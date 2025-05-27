#!/bin/bash

# 供应者
xterm -e "./supplier" &

# 有烟草的抽烟者
xterm -e "./smoker_tobacco" &

# 有纸的抽烟者
xterm -e "./smoker_paper" &

# 有胶水的抽烟者
xterm -e "./smoker_glue" &

echo "已启动所有程序。"
