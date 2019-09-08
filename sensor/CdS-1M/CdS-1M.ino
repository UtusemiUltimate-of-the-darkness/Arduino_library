/**
 * ファイル名 : I2C.ino
 * 作成者 : 命を燃やせない死んでない闇の空蝉ultimate
 * 最終更新日 : 2019/9/8
 * バージョン : 2.0.0
 *
 * 更新履歴
 *   v0.0.0
 *     9軸センサ(MPU9250)の加速度取得関数作成
 *     9軸センサ(MPU9250)の温度取得関数作成
 *   v0.0.1
 *     I2C通信読み出す際の一時格納データを返り血とした．
 *   v1.0.0
 *     記述の整理
 *     I2C通信の読み書きの関数の改良
 *     9軸センサMPU-9250の各データの読み込み関数の記述
 *   v1.1.0
 *     SPI通信の記述
 *   v1.2.1
 *     可読性の向上
 *   v1.3.0
 *     SPI通信初期化関数のスレーブ識別線除外
 *     接続ピンをマクロで設定
 *   v1.4.0
 *     MPU9250温度取得関数返り血の設定
 *     ADXL345SPI通信での加速度取得関数追加
 *   v1.5.0
 *     ADXL345 I2C通信での加速度取得関数の追加
 *     ADXL345 加速度に直す式の改良
 *     「SPI.begin()」の除外
 *   v1.6.0
 *     ADXL345 SPI通信で加速度取得関数の追加
 *   v1.6.1
 *     9軸センサ各センサ感度記述法改良
 *   v2.0.0
 *     センサ，通信機能ごとにファイル分け
*/

// ライブラリをインクルード
#include <math.h>  // 算術ライブラリ

/**
 * 関数名 : setup
 * 引数 : なし
 * 処理 : 最初に1度だけ実行され，各ピンの設定や初期化を記述する
 * 返り値 : なし
*/
void setup () {
    // put your setup code here, to run once:

}

/**
 * 関数名 : serialEvent
 * 引数 : なし
 * 処理 : シリアル入力があったときに割り込み処理を行う
 * 返り値 : なし
*/
void loop () {
    // put your main code here, to run repeatedly:

}

/**
 * 関数名 : CdS1M
 * 引数 : analogPin : HIH4030が接続されているピン番号
 * 処理 : 照度を取得
 * 返り値 : lx : 湿度 [ lux ]
*/
float CdS1M ( int analogPin ) {

    int aIn = analogRead ( analogPin );  // センサ出力値読み込み
    float volt = val2 * 5.0 / 1023.0 ;  // 電圧に直す
    float resister = 10000 * volt / ( 5.0 - volt );  // 抵抗値を計算

    float lx = 4050000 * pow ( resister , -1.34 );  // 照度に直す

    return lx;  // 湿度を返す
}
