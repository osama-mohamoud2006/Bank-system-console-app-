#!/bin/bash

# 🔁 Change directory to the project
project_dir="E:/projects/c++ course/07 - Algorithms & Problem Solving Level 3/Project 1& Extension"
cd "$project_dir" || exit

# 🗓️ Create or read project creation date
created_file=".created_at"
if [ ! -f "$created_file" ]; then
    created_date=$(date '+%Y-%m-%d_%H-%M-%S')
    echo "$created_date" > "$created_file"
    echo "🆕 Created project date: $created_date"
else
    created_date=$(cat "$created_file")
    echo "📅 Project originally created at: $created_date"
fi

# 🧷 Create snapshot if not exists
snapshot_dir="E:/projects/_snapshots_level_three"
snapshot_path="$snapshot_dir/$created_date"

if [ ! -d "$snapshot_path" ]; then
    mkdir -p "$snapshot_path"
    cp -r "$project_dir" "$snapshot_path"
    echo "📁 Snapshot created at: $snapshot_path"
else
    echo "📦 Snapshot already exists at: $snapshot_path"
fi

# ⛔ Ensure .gitignore exists and includes .vs/
gitignore_file=".gitignore"
if [ ! -f "$gitignore_file" ]; then
    echo ".vs/" > "$gitignore_file"
else
    grep -qxF ".vs/" "$gitignore_file" || echo ".vs/" >> "$gitignore_file"
fi

# 🔥 Remove .vs/ from Git index if tracked
if git ls-files --error-unmatch ".vs/" > /dev/null 2>&1; then
    git rm -r --cached .vs/
fi

# 🧠 Git operations
git remote remove origin 2>/dev/null
git remote add origin "https://github.com/osama-mohamoud2006/Bank-system-console-app-"

git pull origin main --rebase

git add -u
git add .

commit_msg="Auto commit: $(date '+%Y-%m-%d %H:%M:%S')"
git commit -m "$commit_msg" --quiet || echo "⚠️ Nothing to commit."

git push -u origin main --quiet
