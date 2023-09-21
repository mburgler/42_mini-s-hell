#!/bin/bash

# Check if in a Git repository
git rev-parse --is-inside-work-tree > /dev/null 2>&1
if [ $? -ne 0 ]; then
  echo "Not a Git repository. Exiting."
  exit 1
fi

# Proceed with Git operations
current_time=$(date +"%Y-%m-%d %H:%M:%S")
username=$(whoami)
commit_message="commit $current_time by $username"

git add .
git commit -m "$commit_message"

if [ $? -eq 0 ]; then
  git push
  if [ $? -eq 0 ]; then
    echo -e "\033[0;32m>>> SUCCESSFUL COMMIT <<<\033[0m"
  else
    echo -e "\033[0;31m>>> PUSH FAILED <<<\033[0m"
  fi
else
  echo -e "\033[0;31m>>> COMMIT FAILED <<<\033[0m"
fi

