3D Shooting Game "StarFox"
==========================

![Graph](https://github.com/takayuki5168/StarFox/blob/master/videos/starfox_video.gif)

多種の操作方法を可能とする3Dシューティングゲーム
キーボード、Wiiリモコン、赤い物体の位置の3種類の入力方法がある
元ネタは任天堂のStarFox64


## 環境構築
Wiiリモコンと`Bluetooth`通信するために`Python`の`cwiid`というモジュールをインストール
```shell
$ sudo apt-get install python-cwiid
```
その他`OpenCV, OpenGL`を使用しているので適宜環境構築するように


## コンパイル
```shell
mkdir build
cd build
cmake ..
make
```


## 実行
1.キーボード入力モード
```shell
$ ./main
```
使用キーは`src/gl.cpp`の`keyboard`関数を参照

2.Wiiリモコン入力モード
ターミナルを2つ開く等してターミナルを二画面開く
片方のターミナルで
```shell
$ python python/main.py
```
を実行した直後Wiiリモコンの1,2ボタンを同時押しすることでPCとWiiリモコンをペアリング
その後、もう片方のターミナルで
```shell
$ ./main -w
```
を実行する

3.VR(赤い物体の位置を入力とする)モード
```shell
$ ./main -v
```
数cm程度の赤い物体を手に持ちパソコンのカメラに収まる程度に移動させて入力とする
