# IT Operations Log & Incident Monitor

A dual-interface log analysis and incident alerting tool built with **C++** (CLI engine) and **HTML/CSS/JavaScript** (Web Dashboard) to help IT support teams detect critical server failures.

## Features
- **Automated Log Classification:** Scans server logs to categorize `INFO`, `WARNING`, and `ERROR` events using `O(1)` hash map lookups.
- **P1 Incident Alerting:** Automatically triggers a Priority-1 escalation alert when error thresholds are crossed.
- **Interactive Web Dashboard:** Supports uploading custom `.txt`/`.log` files, live keyword filtering, severity toggles, and one-click `incident_report.txt` export.

## Files Included
- `main.cpp` — Command-Line Interface (CLI) log analyzer built with C++ STL (`unordered_map`, `vector`) and `fstream`.
- `index.html` — Responsive web dashboard using HTML5, CSS3, and JavaScript (`FileReader` & `Blob` APIs).
