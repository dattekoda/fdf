# fdf

## minilibxとは
minilibxはグラフィカルインターフェースを提供するライブラリで、ウィンドウの拡張縮小、マウスカーソルの位置に至るまでを入力として受取って出力することができる。  
これは従来使われていたX11がベースになっていて2025年の現在からすると太古のプロトコルと言える。  
それを42生が扱えるようにしたものがminilibxライブラリ。  
現在のGUIのほとんどはWaylandaがベースになっている。

## mlx_imgとは
minilibxが提供するrender関数として、mlx_pixel_put()関数がある。  
この関数は与えられた、ディスプレイに直接ピクセルを描写するためにレンダーが重なったときの処理が不自然になる。  
いわゆるフリッカーのような現象が発生する。  
これを防ぐために、一旦レンダーする情報を格納して、一気に描写するような仕組みを採用することで自然なGUIとして使うことが可能。  
```c
typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
}	t_img;
```
上記の構造体にレンダーされる情報を一旦格納する。  
### addr
>`char`型の配列にポインタを受け取らせることで1バイトずつたどっていくことを意味する。  
注意しなければならないのは、これは1ピクセルずつではない。  
1ピクセルの容量は(4ビット) * 8 = 32ビット = 4バイトとなる。  
具体的には以下  
0x00000000  
0x、これは16進数で格納されているという意味となる。  
つまり、左から順番に一つ一つの数字が16パターンの数字を表すことができる。  
この8つの数字を2桁の数字が4つ連続しているという具合に考える。  
色はRGBの情報として格納されている。  
0x00<span style="color: red">FF</span><span style="color: green">00</span><span style="color: blue">FF</span>  
→この例だと<span style="color: red">Red</span>の強さが255、<span style="color: green">Green</span>の強さが0、<span style="color: blue">Blue</span> の強さが255として捉える。  

## 2025/08/07
mapのheightが0のときにセグフォするバグを修正。
