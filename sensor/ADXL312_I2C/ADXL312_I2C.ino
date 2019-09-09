/**
 * ファイル名 : ADXL312_I2C.ino
 * 作成者 : 命を燃やせない死んでない闇の空蝉ultimate
 * 最終更新日 : 2019/9/9
 * バージョン : 2.1.0
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
 *   v2.1.0
 *     3軸加速度センサ ( ADXL312 ) 追加
 *     測距センサ ( GP2Y0A21YK ) の追加
 *     温度センサ ( LM35 ) の追加
*/


// ライブラリをインクルード
#include <Wire.h>  // I2C通信に関するライブラリ

#define ADXL312 ( 0x53 )  // スレーブデバイスのアドレス(SDO/ALT グランド接続)
#define ADXL312_FIRST_DATA_ADDR ( 0x32 )  // 加速度データ格納頭レジスタ

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


/*****************
 * I2C R/W
 *****************/

/**
 * 関数名 : readI2C
 * 引数 : deviceAddr : デバイスアドレス, registerAddr : レジスタアドレス, readByteNum : 読み込むバイト数
 * 処理 : 指定されたデバイスのレジスタから値を読み出す
 * 返り血 : readI2Cbuf : 読み込んだ値の配列
 */
byte readI2Cbuf [ 6 ];  // I2C通信で読み出す最大データ数の指定
void readI2C ( byte deviceAddr , byte registerAddr , int readByteNum ) {

    int8_t i = 0;  // 配列の添字

    Wire.beginTransmission ( deviceAddr );  // 読み出すデバイスのスレーブアドレスを指定
    Wire.write ( registerAddr );            // 読み出すレジスタの開始地点の書き込み
    Wire.endTransmission ( false );         // 通信を一旦終了

    Wire.requestFrom ( deviceAddr , readByteNum );  // データの要求
    // 読み込むデータがなくなるまで値を読む
    while ( Wire.available () ) {

        readI2Cbuf [ i++ ] = Wire.read ();  // 読み込んだ値を配列に格納
    }
}

/**
 * 関数名 : writeI2C
 * 引数 : deviceAddr : デバイスアドレス(スレーブアドレス), registerAddr : レジスタアドレス, value : 書き込む値
 * 処理 : 指定されたデバイスのレジスタに値を書き込む
 * 返り血 : なし
 */
void writeI2C ( byte deviceAddr , byte registerAddr , byte value ) {

    Wire.beginTransmission ( deviceAddr );  // 書き込むデバイスのスレーブアドレスの指定
    Wire.write ( registerAddr );            // 書き込むレジスタアドレスの指定
    Wire.write ( value );                   // 値を書き込む
    Wire.endTransmission ();                // 通信の終了
}


/*****************
 * 3軸デジタル加速度センサI2C ( ADXL312 )
*****************/

/**
 * 関数名 : setup_ADXL312_I2C
 * 引数 : なし
 * 処理 : 3軸加速度センサADXL345の初期設定(I2C通信)
 * 返り値 : なし
*/
void setup_ADXL312_I2C () {

    writeI2C ( ADXL312 , 0x31 , 0x00 );  // DATA_FORMAT(レンジ設定)1.5G
    // writeI2C ( ADXL312 , 0x31 , 0x01 );  // DATA_FORMAT(レンジ設定)3.0G
    // writeI2C ( ADXL312 , 0x31 , 0x10 );  // DATA_FORMAT(レンジ設定)6.0G
    // writeI2C ( ADXL312 , 0x31 , 0x11 );  // DATA_FORMAT(レンジ設定)12G
    writeI2C ( ADXL312 , 0x2d , 0x08 );  // PWER_CTL
}

/**
 * 関数名 : setup_ADXL345_I2C
 * 引数 : なし
 * 処理 : 3軸加速度センサADXL345の初期設定(I2C通信)
 * 返り値 : なし
*/
float ADXL312AccelXG , ADXL312AccelYG , ADXL312AccelZG;  // 加速度G
void get_ADXL312_I2C () {

    float resolution = 0.0029;  // 分解能

    readI2C ( ADXL312 , ADXL312_FIRST_DATA_ADDR , 6 );  // 値を読み込む

    // 加速度データを格納
    int16_t x = ( ( ( int ) readI2Cbuf [ 1 ] ) << 8 ) | readI2Cbuf [ 0 ];
    int16_t y = ( ( ( int ) readI2Cbuf [ 3 ] ) << 8 ) | readI2Cbuf [ 2 ];
    int16_t z = ( ( ( int ) readI2Cbuf [ 5 ] ) << 8 ) | readI2Cbuf [ 4 ];

    // 加速度に直す
    ADXL312AccelXG = resolution * x;
    ADXL312AccelYG = resolution * y;
    ADXL312AccelZG = resolution * z;

}
