#!bin/bash

python3 decrese.py
echo "decrese OK!"
python3 transcode.py < data.les > code.les
echo "encode OK!"
python3 ../Python/weakmain.py < code.les > stdout.les
echo "parse OK!"
python3 recall.py
