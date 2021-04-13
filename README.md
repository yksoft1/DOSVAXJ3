DOSVAXJ3
====

DOSbox の AX, J-3100, DOS/V 対応版です。  
akm 氏による DOSbox の派生版 DOSVAX 4000AX11 をベースとし、Wengier Wu 氏による DOSBox-lfn の修正を取り込んでいます。  
SDL は IME 対応の [SDL-IM-plus](https://github.com/nanshiki/SDL-IM-plus) を使用してください。  
実際に使用している jp.kl のソースは key_jp の jp.key です。  

DOSVAXJ3 [README](https://github.com/nanshiki/DOSVAXJ3/blob/master/README.txt)　[技術情報](https://github.com/nanshiki/DOSVAXJ3/blob/master/Knowledge.txt)  

DOSBox [README](https://github.com/nanshiki/DOSVAXJ3/blob/master/README_DOSBox.txt)  

## ビルド
### Windows  
Visual Studio 2015 で visualc_net/dosbox.sln を読み込み、ビルドしてください。  
SDL_net, zlib, libpng, pdcurses 等のライブラリをビルドし、リンクできるようにしておいてください。  

### Linux  
$ ./autogen.sh  
$ ./configure  
$ make  
$ sudo make install  
SDL-IM-plus をビルド、インストールしておく必要があります。  
Debian 系の場合、automake libsdl-sound1.2 libsdl-net1.2 あたりをインストールしておいてください。  
CentOS、Fedora 等で日本語が表示されない場合、xorg-x11-fonts-misc をインストールしてください。  
Raspberry Pi で日本語が表示されない場合 xfonts-base をインストールしてください。Raspberry Pi OS 2021-1-11版で日本語表示を確認しています。  
実行ファイル名は dosboxj に、設定ファイル名も dosboxj-conf に変更になっています。  

## ライセンス
GPL v2
