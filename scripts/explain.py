import os, re, json, pathlib, requests
from typing import Optional, Tuple

# ---- Config ----
REPO_ROOT = pathlib.Path(__file__).resolve().parents[1]
CODE_DIRS = ["leetcode", "codechef"]
CODE_EXTS = {".py", ".cpp", ".cc", ".cxx", ".c", ".java", ".js", ".ts", ".go", ".rb", ".kt", ".cs", ".rs"}

HEADERS = {"User-Agent": "Mozilla/5.0 (WOW-sync-bot)"}
EXA_API_KEY = os.getenv("OPENAI_API_KEY")  # Your Exa API key

if not EXA_API_KEY:
    raise ValueError("❌ Exa API key not found. Set OPENAI_API_KEY in your environment or secrets.")


# ---- Helper Functions ----
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


def infer_platform_and_title(path: pathlib.Path) -> Tuple[str, str]:
    parts = path.parts
    platform = "Unknown"
    title = path.stem
    if "leetcode" in parts:
        platform = "LeetCode"
        folder = path.parent.name
        title = re.sub(r"^\d+[-_.]+", "", folder).replace("-", " ").title()
    elif "codechef" in parts:
        platform = "CodeChef"
        folder = path.parent.name
        title = folder
    return platform, title


def fetch_codechef_description(code: str) -> Optional[str]:
    url = f"https://www.codechef.com/problems/{code}"
    try:
        r = requests.get(url, headers=HEADERS, timeout=20)
        if r.status_code != 200:
            return None
        from bs4 import BeautifulSoup
        soup = BeautifulSoup(r.text, "html.parser")
        main = soup.find(id="problem-statement") or soup.find("div", class_="problem-statement") or soup.find("section")
        text = main.get_text("\n").strip() if main else None
        return text
    except Exception:
        return None


def fetch_leetcode_description(slug: str) -> Optional[str]:
    url = f"https://leetcode.com/problems/{slug}/description/"
    try:
        r = requests.get(url, headers=HEADERS, timeout=20)
        if r.status_code != 200:
            return None
        from bs4 import BeautifulSoup
        soup = BeautifulSoup(r.text, "html.parser")
        article = soup.find("div", attrs={"data-track-load":"description_content"}) or soup.find("article") or soup.find("div")
        return article.get_text("\n").strip() if article else None
    except Exception:
        return None


def exa_explain(problem_title: str, platform: str, code: str, description: Optional[str]) -> Optional[str]:
    """
    Calls Exa AI API to generate a beginner-friendly explanation of the code/problem.
    """
    query_text = f"""Explain the following {platform} problem and solution clearly for beginners:

Title: {problem_title}
Problem Description: {description or 'N/A'}

Solution Code:
{code}

Include:
1) Summary of the problem
2) Step-by-step approach
3) Time & Space Complexity
4) Edge cases
5) Brief example walkthrough
"""
    url = "https://api.exa.ai/search"
    headers = {
        "x-api-key": EXA_API_KEY,
        "Content-Type": "application/json"
    }
    payload = {
        "query": query_text,
        "text": True,
        "num_results": 1
    }
    try:
        resp = requests.post(url, headers=headers, json=payload, timeout=60)
        resp.raise_for_status()
        data = resp.json()
        results = data.get("results", [])
        if results:
            return results[0].get("autopromptString") or results[0].get("title") or "*(Explanation not returned by Exa)*"
        return "*(No explanation returned by Exa)*"
    except Exception as e:
        return f"*(Error fetching explanation: {e})*"


def write_readme(dir_path: pathlib.Path, title: str, platform: str, code_text: str, desc: Optional[str], ai_exp: Optional[str]):
    readme = dir_path / "README.md"
    if readme.exists():
        existing = read_text(readme).strip()
        if len(existing) > 20:
            return
    snippet = "\n".join(code_text.splitlines()[:30])
    generated = ai_exp or "*(Add your explanation here)*"
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

"""
readme.write_text(content, encoding="utf-8")


def leetcode_guess_slug(folder: str) -> str:
    s = folder.strip().lower()
    s = s.replace(" ", "-")
    s = re.sub(r"^\d+[-_.]+", "", s)
    s = re.sub(r"[^a-z0-9-]", "", s)
    return s


# ---- Main Workflow ----
def main():
    files = find_code_files()
    changed = False
    for code_file in files:
        dir_path = code_file.parent
        readme = dir_path / "README.md"
        if readme.exists():
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
        ai_exp = exa_explain(title, platform, code_text, desc)
        write_readme(dir_path, title, platform, code_text, desc, ai_exp)
        changed = True
    if changed:
        print("✅ README files created/updated.")
    else:
        print("ℹ️ No changes needed.")


if __name__ == "__main__":
    main()
