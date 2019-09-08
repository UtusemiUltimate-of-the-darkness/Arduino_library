/**
 * ファイル名 : SPI.ino
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
#include <SPI.h>   // SPI通信に関するライブラリ

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
 * SPI setup,R/W
 *****************/
// 接続ピン
#define SCK 13
#define MOSI 11
#define MISO 12
#define SS1 10


/**
 * 関数名: setup_SPI
 * 処理: SPI通信の初期化処理
 * 引数: sck, mosi, miso : スレーブデバイスの各通信用ピン，spiMode : SPI通信のモード
 * 返り血 : なし
*/
void setup_SPI ( int sck , int mosi , int miso , byte spiMode ) {

    // 各ピン設定
    pinMode ( sck , OUTPUT );
    pinMode ( mosi , OUTPUT );
    pinMode ( miso , INPUT );

    // spi通信モードの設定
    switch ( spiMode ) {
        case 0x00 :
            SPI.setDataMode ( SPI_MODE0 );
            break;

        case 0x01 :
            SPI.setDataMode ( SPI_MODE1 );
            break;

        case 0x02 :
            SPI.setDataMode ( SPI_MODE2 );
            break;

        case 0x03 :
            SPI.setDataMode ( SPI_MODE3 );
            break;

        default :
            SPI.setDataMode ( SPI_MODE3 );
            break;
    }

    SPI.setBitOrder ( MSBFIRST );
}

/**
 * 関数名: writeSPI
 * 処理: スレーブデバイスに書き込み
 * 引数: SS: スレーブデバイス識別線，registerAddr: レジスタアドレス，value: 書き込む値
 * 返り血 : なし
*/
void writeSPI ( int ss , byte registerAddr , byte value ) {

    digitalWrite ( ss , LOW );      // 通信の開始
    SPI.transfer ( registerAddr );  // 書き込むレジスタのアドレス
    SPI.transfer ( value );         // 書き込む値
    digitalWrite ( ss , HIGH );     // 通信の終了
}

/**
 * 関数名: readSPI
 * 処理: スレーブデバイスから値の読み出し
 * 引数: ss: 信号線，registerAddr: レジスタアドレス，len: 読み出す長さ
 * 返り血 : なし
*/
byte readSPIbuf [ readSPI_maxByteNum ];
void readSPI ( int ss , byte registerAddr , int len ) {

    char addr = 0x80 | registerAddr;  // 書き込みフラグを立てる(0b10000000)
    // 複数バイト読み出す場合
    if ( len > 1 ) {

        addr = addr | 0x40;  // 複数バイトフラグを立てる(0b1000000)
    }

    digitalWrite ( ss , LOW );  // 通信の開始
    SPI.transfer ( addr );  // 読み出すレジスタのアドレス
    // 値を読み出す
    for ( int i = 0; i < len; i++ ) {

        readSPIbuf [ i ] = SPI.transfer ( 0x00 );  // 読み出したデータを格納
    }

    digitalWrite ( ss , HIGH );  // 通信の終了
}
