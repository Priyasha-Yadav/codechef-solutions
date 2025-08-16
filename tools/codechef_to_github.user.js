// ==UserScript==
// @name         CodeChef → GitHub Uploader (WOW)
// @namespace    wow-sync
// @version      1.0
// @description  Adds a "Push to GitHub" button on CodeChef submit/problem pages to upload your code to your repo with one click
// @author       You
// @match        https://www.codechef.com/*
// @grant        none
// ==/UserScript==

(function() {
  'use strict';

  // ---------- EDIT THESE 3 LINES ----------
  const GITHUB_USERNAME = "YOUR_GITHUB_USERNAME";
  const REPO = "YOUR_REPO_NAME";
  const GH_TOKEN = "YOUR_GITHUB_PAT_TOKEN"; // classic token with 'repo' or 'public_repo' scope
  // ----------------------------------------

  // Helper: base64 encode unicode safely
  function b64(str) {
    return btoa(unescape(encodeURIComponent(str)));
  }

  function getProblemCode() {
    // URL patterns like: https://www.codechef.com/submit/PROBLEM or /problems/PROBLEM
    const m = location.pathname.match(/\/(submit|problems|status)\/([A-Za-z0-9_\-]+)/);
    return m ? m[2] : (document.title.split('|')[0].trim() || "UNKNOWN");
  }

  function guessLangExt() {
    // Try to read language selector; fallback to .txt
    const selects = Array.from(document.querySelectorAll('select'));
    const langSel = selects.find(s => /language/i.test(s.id) || /language/i.test(s.name) || /language/i.test(s.outerHTML));
    const val = langSel ? (langSel.value || '').toLowerCase() : '';
    if (val.includes('cpp') || val.includes('g++') || val.includes('c++')) return '.cpp';
    if (val.includes('java')) return '.java';
    if (val.includes('python')) return '.py';
    if (val.includes('c ') || val === 'c') return '.c';
    if (val.includes('javascript') || val.includes('node')) return '.js';
    if (val.includes('go')) return '.go';
    if (val.includes('kotlin')) return '.kt';
    if (val.includes('csharp') || val.includes('c#')) return '.cs';
    if (val.includes('rust')) return '.rs';
    return '.txt';
  }

  function getSourceCode() {
    // Try common textareas
    const ta = document.querySelector('textarea') || document.querySelector('code') || document.querySelector('pre');
    if (ta && ta.value) return ta.value;
    if (ta && ta.textContent) return ta.textContent;
    // If not found, prompt user
    return prompt('Paste your accepted solution code to push to GitHub:' ) || '';
  }

  async function pushToGitHub() {
    const prob = getProblemCode();
    if (!prob) return alert('Could not determine problem code.');
    const ext = guessLangExt();
    const code = getSourceCode();
    if (!code.trim()) return alert('No code found.');

    const folder = `codechef/${prob}`;
    const ts = new Date().toISOString().replace(/[:.]/g, '-');
    const codePath = `${folder}/solution-${ts}${ext}`;
    const readmePath = `${folder}/README.md`;

    const headers = {
      'Authorization': `Bearer ${GH_TOKEN}`,
      'Accept': 'application/vnd.github+json'
    };

    // Create/Update code file
    const codeResp = await fetch(`https://api.github.com/repos/${GITHUB_USERNAME}/${REPO}/contents/${codePath}`, {
      method: 'PUT',
      headers,
      body: JSON.stringify({
        message: `feat(codechef): ${prob} solution`,
        content: b64(code),
        branch: 'main'
      })
    });
    if (!codeResp.ok) {
      const msg = await codeResp.text();
      return alert('GitHub code upload failed: ' + msg);
    }

    // Create README placeholder (only if not exists)
    const readmeRespCheck = await fetch(`https://api.github.com/repos/${GITHUB_USERNAME}/${REPO}/contents/${readmePath}`, {
      headers
    });
    if (readmeRespCheck.status === 404) {
      const tmpl = `# ${prob} (CodeChef)\n\n_(Auto-created. A GitHub Action will fill in explanation later.)_\n`;
      const readmeResp = await fetch(`https://api.github.com/repos/${GITHUB_USERNAME}/${REPO}/contents/${readmePath}`, {
        method: 'PUT',
        headers,
        body: JSON.stringify({
          message: `docs(codechef): add README for ${prob}`,
          content: b64(tmpl),
          branch: 'main'
        })
      });
      if (!readmeResp.ok) {
        const msg = await readmeResp.text();
        return alert('GitHub README upload failed: ' + msg);
      }
    }

    alert('Pushed to GitHub! The README will be auto-generated in a minute.');
  }

  function addButton() {
    const btn = document.createElement('button');
    btn.textContent = 'Push to GitHub ✅';
    btn.style.position = 'fixed';
    btn.style.bottom = '20px';
    btn.style.right = '20px';
    btn.style.padding = '10px 14px';
    btn.style.zIndex = 99999;
    btn.style.border = 'none';
    btn.style.borderRadius = '8px';
    btn.style.fontWeight = 'bold';
    btn.style.cursor = 'pointer';
    btn.style.boxShadow = '0 2px 8px rgba(0,0,0,0.2)';
    btn.addEventListener('click', pushToGitHub);
    document.body.appendChild(btn);
  }

  // Add button on load
  window.addEventListener('load', addButton);
})();
