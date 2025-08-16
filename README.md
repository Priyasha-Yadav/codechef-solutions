# WOW Auto Sync (LeetCode + CodeChef → GitHub with Explanations)

This repo is set up to:
- ✅ Auto-commit LeetCode solutions (use the **LeetHub** browser extension)
- ✅ One-click upload CodeChef solutions (via the included **Tampermonkey** userscript)
- 🔮 Auto-generate **README** explanations for each problem using a GitHub Action
  - If you add `OPENAI_API_KEY` to repo secrets, explanations are AI-generated
  - If not, a neat template is created for you to fill in

## Quick Start
1) Install **LeetHub** (Chrome) and connect it to this repo for LeetCode.
2) Install **Tampermonkey** (Chrome/Firefox), add `tools/codechef_to_github.user.js`, and set your:
   - `GITHUB_USERNAME`
   - `REPO`
   - `GH_TOKEN` (GitHub PAT with `repo` scope, or `public_repo` for public repos)
3) (Optional) Add **OPENAI_API_KEY** to this repo's **Settings → Secrets and variables → Actions → New repository secret**.
4) Commit any new solution (or click the CodeChef button). The workflow `.github/workflows/explain.yml` will create/update `README.md` inside each problem folder.

Folders to use:
```
leetcode/<problem-folder>/*.ext
codechef/<PROBLEM_CODE>/*.ext
```
