# 🚀  Auto‑Sync Setup 

Goal: When you solve problems on **LeetCode** or **CodeChef**, your code goes to **GitHub** automatically and a **README** with explanation appears.

You’ll do three tiny things:
1) Turn on LeetCode → GitHub (via a browser extension)
2) Add a magic button on CodeChef to upload with one click
3) Let GitHub write the READMEs for you (action runs by itself)

---

## ✅ Step 1 — Make your GitHub repo
1. Go to **github.com → New repository**
2. Name it: `coding-solutions` (or anything)
3. Click **Create repository**
4. Click **Add file → Upload files**
5. Clone the repo

> You should now see folders: `.github/`, `scripts/`, `tools/`, and files `requirements.txt`, `README.md`.

---

## ✅ Step 2 — (Optional) Turn on AI explanations
This makes the README explanations automatic.

1. Open your repo → **Settings → Secrets and variables → Actions → New repository secret**
2. Name: `OPENAI_API_KEY` → Value: your OpenAI key → **Add secret**

If you don’t have a key, skip this. The action will still create a tidy README template.

---

## ✅ Step 3 — LeetCode → GitHub (fully automatic)
1. Install **LeetHub** extension (Chrome Web Store)
2. Open the extension → **Connect GitHub** → pick the repo you just made
3. Solve a problem on LeetCode and click **Submit** → it will push to a path like:
```
leetcode/0001-two-sum/solution.cpp
```
The GitHub Action will later add `README.md` inside that folder.

> Tip: First time, LeetHub may ask to create a repo for you. Choose **Use existing** and pick your repo.

---

## ✅ Step 4 — CodeChef → GitHub (one‑click button)
We’ll add a tiny **Tampermonkey** script that shows a **“Push to GitHub ✅”** button on CodeChef pages.

1. Install **Tampermonkey** (Chrome/Firefox extension)
2. Open Tampermonkey → **Create a new script**
3. From your repo files, open **`tools/codechef_to_github.user.js`** → copy all → paste into Tampermonkey
4. Edit the **top 3 lines** in the script:
   ```js
   const GITHUB_USERNAME = "YOUR_GITHUB_USERNAME";
   const REPO = "YOUR_REPO_NAME"; // same repo from Step 1
   const GH_TOKEN = "YOUR_GITHUB_PAT_TOKEN"; // create below
   ```
5. Create a **GitHub PAT (token)**: GitHub → **Settings → Developer settings → Personal access tokens → Tokens (classic)** → **Generate new token** → Scopes: `repo` (or `public_repo` if your repo is public) → copy token and paste into `GH_TOKEN`.
6. Go to a CodeChef **Submit** or **Problem** page. You’ll see a floating button **“Push to GitHub ✅”** (bottom‑right).
7. Click the button after an **Accepted** solution. It uploads your code to:
```
codechef/PROBLEM_CODE/solution-YYYY-MM-DD..ext
```
The Action will add `README.md` with explanation.

> If the script can’t find your code automatically, it will ask you to paste it. Easy.

---

## ✅ Step 5 — Let GitHub write the README for each problem
- The repo already contains a workflow: `.github/workflows/explain.yml`
- It runs when you push a new solution (LeetCode or CodeChef) **and** once daily
- It looks inside `leetcode/` and `codechef/` folders:
  - If a problem folder has code but no `README.md`, it creates one
  - If you added `OPENAI_API_KEY`, it asks AI to write the explanation
  - Otherwise it creates a clean template for you to fill

You’ll see commits like: _“add/update problem READMEs with explanations”_

---

## ✅ Folder layout (what your repo will look like)
```
.github/workflows/explain.yml      ← the GitHub Action
scripts/explain.py                 ← script that fetches statements & writes README
requirements.txt                   ← Python deps for the Action
tools/codechef_to_github.user.js   ← the one‑click CodeChef uploader (for Tampermonkey)

leetcode/0001-two-sum/solution.cpp
leetcode/0002-add-two-numbers/solution.java
codechef/FLOW001/solution-2025-08-15.py
```

---

## 🧼 Troubleshooting (super simple)
- **No README created?** Wait ~1–2 minutes and refresh the repo page (the Action needs to run).
- **LeetHub didn’t push?** Open the extension and re‑connect the repo.
- **CodeChef button not visible?** Refresh the page or reopen the Tampermonkey dashboard and ensure the script is **Enabled**.
- **AI explanation not showing?** Make sure you added `OPENAI_API_KEY` in repo **Secrets**.

---

## 🧠 How it works (short version)
- LeetHub uploads LeetCode code. Tampermonkey uploads CodeChef code.
- A GitHub Action (already included) runs a Python script that:
  - Grabs the problem code
  - Tries to fetch the problem statement (best effort)
  - Optionally asks AI to write the explanation
  - Saves a `README.md` right next to your code

You do nothing extra. Just solve and click.

---

## 🎯 You’re done!
Solve problems. Watch your repo fill up with folders — each with your code **and** a neat explanation.
