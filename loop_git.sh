#!/bin/bash

# 确保是在一个git仓库内
if [ ! -d ".git" ]; then
  echo "当前目录不是一个git仓库，正在初始化..."
  git init
fi

for i in {1..5}
do
  echo "第 $i 次循环"

  # 创建 1.cpp，写点内容
  echo "// 这是第 $i 个 1.cpp 文件" > 1.cpp

  # git add 和 commit
  git add 1.cpp
  git commit -m "第 $i 次：添加 $i.cpp"

  # 删除 1.cpp
  rm 1.cpp

  # git commit 删除
  git add -u
  git commit -m "第 $i 次：创建 $i.cpp"

done

echo "循环完成。"
