import os, re, base64, json, time, pathlib
from typing import Optional, Tuple
import requests
from bs4 import BeautifulSoup

REPO_ROOT = pathlib.Path(__file__).resolve().parents[1]
CODE_DIRS = ["leetcode", "codechef"]
CODE_EXTS = {".py", ".cpp", ".cc", ".cxx", ".c", ".java", ".js", ".ts", ".go", ".rb", ".kt", ".cs", ".rs"}

HEADERS = {
    "User-Agent": "Mozilla/5.0 (WOW-sync-bot)"
}

def find_code_files():
    results = []
    for base in CODE_DIRS:
        base_path = REPO_ROOT / base
        if not base_path.exists():
            continue
        for p in base_path.rglob("*"):
            if p.is_file() and p.suffix.lower() in CODE_EXTS:
                results.append(p)
    return results

def read_text(p: pathlib.Path) -> str:
    try:
        return p.read_text(encoding="utf-8")
    except Exception:
        return p.read_text(encoding="latin-1", errors="ignore")

def leetcode_guess_slug(folder: str) -> str:
    # common formats: "0001-two-sum", "two-sum", "Two Sum"
    s = folder.strip().lower()
    s = s.replace(" ", "-")
    # drop leading number+dash
    s = re.sub(r"^\d+[-_.]+", "", s)
    # keep only allowed slug chars
    s = re.sub(r"[^a-z0-9-]", "", s)
    return s

def fetch_leetcode_description(slug: str) -> Optional[str]:
    if not slug:
        return None
    # Best-effort: scrape the description page
    url = f"https://leetcode.com/problems/{slug}/description/"
    try:
        r = requests.get(url, headers=HEADERS, timeout=20)
        if r.status_code != 200:
            return None
        soup = BeautifulSoup(r.text, "html.parser")
        # Try common containers
        article = soup.find("div", attrs={"data-track-load":"description_content"})
        if not article:
            article = soup.find("article")
        if not article:
            # fallback: any main content div
            article = soup.find("div")
        text = article.get_text("\n").strip() if article else None
        return text
    except Exception:
        return None

def fetch_codechef_description(code: str) -> Optional[str]:
    # Code is like "FLOW001"
    url = f"https://www.codechef.com/problems/{code}"
    try:
        r = requests.get(url, headers=HEADERS, timeout=20)
        if r.status_code != 200:
            return None
        soup = BeautifulSoup(r.text, "html.parser")
        # Try common containers
        main = soup.find(id="problem-statement") or soup.find("div", class_="problem-statement") or soup.find("section")
        text = main.get_text("\n").strip() if main else None
        return text
    except Exception:
        return None

def openai_explain(problem_title: str, platform: str, code: str, description: Optional[str]) -> Optional[str]:
    api_key = os.getenv("OPENAI_API_KEY")
    if not api_key:
        return None
    prompt = f"""You are an expert competitive programmer and teacher.
Write a clear, beginner-friendly explanation for the following {platform} problem.
Include:
1) One-sentence summary of the problem
2) Intuition and step-by-step approach
3) Time and space complexity (Big-O)
4) Edge cases
5) Brief walkthrough with a small example
Keep it concise but helpful.

Problem title: {problem_title}
Problem statement (best-effort): {description or 'N/A'}

User's accepted code:
```
{code}
```"""
    data = {
        "model": "gpt-4o-mini",
        "messages": [
            {"role":"system","content":"You write crisp, accurate programming explanations."},
            {"role":"user","content": prompt}
        ],
        "temperature": 0.2,
    }
    try:
        resp = requests.post(
            "https://api.openai.com/v1/chat/completions",
            headers={
                "Authorization": f"Bearer {api_key}",
                "Content-Type": "application/json"
            },
            data=json.dumps(data),
            timeout=60
        )
        if resp.status_code != 200:
            # Fallback to a widely available model name
            data["model"] = "gpt-3.5-turbo"
            resp = requests.post(
                "https://api.openai.com/v1/chat/completions",
                headers={
                    "Authorization": f"Bearer {api_key}",
                    "Content-Type": "application/json"
                },
                data=json.dumps(data),
                timeout=60
            )
        j = resp.json()
        content = j.get("choices", [{}])[0].get("message", {}).get("content")
        return content
    except Exception:
        return None

def write_readme(dir_path: pathlib.Path, title: str, platform: str, code_text: str, desc: Optional[str], ai_exp: Optional[str]):
    readme = dir_path / "README.md"
    if readme.exists():
        # Update only if it's empty-ish
        existing = read_text(readme).strip()
        if len(existing) > 20:
            return
    snippet = "\n".join(code_text.splitlines()[:30])
    generated = ai_exp or "*(Add your explanation here or set OPENAI_API_KEY in repo secrets for auto-generation.)*"
    content = f"""# {title} ({platform})

## Problem (best-effort summary)
{(desc[:1200] + ' ...') if desc and len(desc) > 1200 else (desc or 'Problem description could not be fetched automatically.')}

## Explanation
{generated}

## Complexity
- **Time:** _..._
- **Space:** _..._

## Code (first ~30 lines preview)
```{dir_path.suffix if dir_path.suffix else ''}
{snippet}
```
"""
    readme.write_text(content, encoding="utf-8")

def infer_platform_and_title(path: pathlib.Path) -> Tuple[str, str]:
    # Expect structure like: leetcode/<folder>/solution.ext or codechef/<CODE>/main.ext
    parts = path.parts
    platform = "Unknown"
    title = path.stem
    if "leetcode" in parts:
        platform = "LeetCode"
        # title folder is the parent dir name
        folder = path.parent.name
        # convert to title-ish
        title = re.sub(r"^\d+[-_.]+", "", folder).replace("-", " ").title()
    elif "codechef" in parts:
        platform = "CodeChef"
        folder = path.parent.name  # usually problem code, like FLOW001
        title = folder
    return platform, title

def main():
    files = find_code_files()
    changed = False
    for code_file in files:
        dir_path = code_file.parent
        readme = dir_path / "README.md"
        if readme.exists():
            # skip
            continue
        platform, title = infer_platform_and_title(code_file)
        code_text = read_text(code_file)
        desc = None
        if platform == "LeetCode":
            slug = leetcode_guess_slug(dir_path.name)
            desc = fetch_leetcode_description(slug)
        elif platform == "CodeChef":
            prob_code = dir_path.name.upper()
            desc = fetch_codechef_description(prob_code)
        ai_exp = openai_explain(title, platform, code_text, desc)
        write_readme(dir_path, title, platform, code_text, desc, ai_exp)
        changed = True
    if changed:
        print("README files created/updated.")
    else:
        print("No changes needed.")

if __name__ == "__main__":
    main()
