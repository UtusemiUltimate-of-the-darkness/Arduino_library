/**
 * ファイル名: Arduino_library.ino
 * 作成者: 命を燃やせない死んでない闇の空蝉ultimate
 * 最終更新日: 2019-4-19
 * バージョン: 1.6.0
 *
 * 機能
 *   通信系
 *     I2C R/W
 *     SPI R/W
 *   センサ系
 *     MPU-9250
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
 *     9軸センサ(MPU-9250)の地磁気測定モードの追加
*/

// ライブラリをインクルード
#include <Wire.h>  // I2C通信に関するライブラリ
#include <SPI.h>   // SPI通信に関するライブラリ
#include <math.h>  // 算術ライブラリ
/**
 * 関数名: setup
 * 引数: なし
 * 処理: 最初に1度だけ実行され，各ピンの設定や初期化を記述する
 * 返り値: なし
*/
void setup () {
    // put your setup code here, to run once:

}

/**
 * 関数名: serialEvent
 * 引数: なし
 * 処理: シリアル入力があったときに割り込み処理を行う
 * 返り値: なし
*/
void serialEvent () {

}

/**
 * 関数名: loop
 * 引数: なし
 * 処理: 無限ループ．繰り返し行う処理を記述
 * 返り値: なし
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
byte readI2Cbuf [ readI2C_maxByteNum ];  // I2C通信で読み出す最大データ数の指定
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
 * SPI setup,R/W
 *****************/
// 接続ピン
#define SCK 13
#define MOSI 11
#define MISO 12

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


/*****************
 * 9軸センサ(MPU-9250)
*****************/
// デバイスのスレーブアドレス
#define MPU9250 ( 0x69 )  // 加速度，角速度
#define AK8963 ( 0x0C )   // 地磁気

// 初期化用アドレス
#define MPU9250_PWR_MGMT1 ( 0x6B )     // 電源管理用レジスタアドレス
#define MPU9250_INT_PIN_CFG ( 0x37 )   // 入力ピンの設定レジスタアドレス
#define AK8963_CNTL1 ( 0x0A )          // 地磁気動作モード設定レジスタアドレス

// 測定レンジNO設定
#define MPU9250_GYRO_CONFIG ( 0x1B )   // 角速度レンジ設定レジスタアドレス
#define MPU9250_ACCEL_CONFIG ( 0x1C )  // 加速度レンジ設定レジスタアドレス

// 角速度の各測定レンジ
#define MPU9250_GYRO_RANGE_250DPS ( 0x00 )   // +-250dps
#define MPU9250_GYRO_RANGE_500DPS ( 0x08 )   // +-500dps
#define MPU9250_GYRO_RANGE_1000DPS ( 0x10 )  // +-1000dps
#define MPU9250_GYRO_RANGE_2000DPS ( 0x18 )  // +-2000dps

// 加速度の各測定レンジ
#define MPU9250_ACCEL_RANGE_2G ( 0x00 )   // +-2g
#define MPU9250_ACCEL_RANGE_4G ( 0x08 )   // +-4g
#define MPU9250_ACCEL_RANGE_8G ( 0x10 )   // +-8g
#define MPU9250_ACCEL_RANGE_16G ( 0x18 )  // +-16g

// 各センサの測定レンジの設定
byte MPU9250AccelRange = MPU9250_ACCEL_RANGE_2G;
byte MPU9250GyroRange = MPU9250_GYRO_RANGE_250DPS;

/**
 * 関数名 : setup_MPU9250
 * 引数 : AK8963Mode : AK8963測定モード
 * 処理 : 9軸センサMPU9250の初期設定関数
 * 返り血 : なし
 */
float MPU9250AccelSensitiv , MPU9250GyroSensitiv;                          // MPU9250各センサの感度
float AK8963CompX_Sensitiv , AK8963CompY_Sensitiv , AK8963CompZ_Sensitiv;  // AK8963地磁気感度
void setup_MPU9250 ( int AK8963Mode ) {

    // センサの書記設定
    writeI2C ( MPU9250 , MPU9250_PWR_MGMT1 , 0x00 );    // 電源管理
    writeI2C ( MPU9250 , MPU9250_INT_PIN_CFG , 0x02 );  // 入力ピンの設定
    writeI2C ( AK8963 , AK8963_CNTL1 , 0x16 );  // 地磁気書記設定

    // センサレンジの設定
    writeI2C ( MPU9250 , MPU9250_ACCEL_CONFIG , MPU9250AccelRange );  // 加速度
    writeI2C ( MPU9250 , MPU9250_GYRO_CONFIG , MPU9250GyroRange );    // 角速度

    // 動作確認
    readI2C ( MPU9250 , 0x75 , 1 );  // 値を読み出し
    Serial.print ( "I am " );
    Serial.println ( readI2Cbuf [ 0 ] , HEX );

    // 加速度感度の設定
    if ( MPU9250AccelRange == 0x00 ) {

        MPU9250AccelSensitiv = pow ( 2 , 2 ) / pow ( 2 , 16 );

    } else if ( MPU9250AccelRange == 0x08 ) {

        MPU9250AccelSensitiv = pow ( 2 , 3 ) / pow ( 2 , 16 );

    } else if ( MPU9250AccelRange == 0x10 ) {

        MPU9250AccelSensitiv = pow ( 2 , 4 ) / pow ( 2 , 16 );

    } else if ( MPU9250AccelRange == 0x08 ) {

        MPU9250AccelSensitiv = pow ( 2 , 5 ) / pow ( 2 , 16 );
    }

    // switch ( MPU9250AccelRange ) {
    //     case /* value */:
    // }

    // 角速度感度の設定
    if ( MPU9250GyroRange == 0x00 ) {

        MPU9250GyroSensitiv = 500 * pow ( 2 , 0 ) / pow ( 2 , 16 );

    } else if ( MPU9250GyroRange == 0x08 ) {

        MPU9250GyroSensitiv = 500 * pow ( 2 , 1 ) / pow ( 2 , 16 );

    } else if ( MPU9250GyroRange == 0x10 ) {

        MPU9250GyroSensitiv = 500 * pow ( 2 , 2 ) / pow ( 2 , 16 );

    } else if ( MPU9250GyroRange == 0x08 ) {

        MPU9250GyroSensitiv = 500 * pow ( 2 , 3 ) / pow ( 2 , 16 );
    }

    // 測定モード設定
    switch ( AK8963Mode ) {
        case 0x00 :
            int val = 0x02;
            break;
        case 0x01 :
            int val = 0x05;
            break;
        case 0x10 :
            int val = 0x12;
            break;
        case 0x11 :
            int val = 0x15;
    }
    writeI2C( AK8963 , AK8963_CNTL1 , val );

    // 地磁気感度調整
    // readI2C ( AK8963 , 0x10 , 3 );
    // AK8963CompX_Sensitiv = ( int ) readI2Cbuf [ 0 ] * ( (  ) + 1 )
    // AK8963CompY_Sensitiv = ( int ) readI2Cbuf [ 1 ] * ( (  ) + 1 )
    // AK8963CompZ_Sensitiv = ( int ) readI2Cbuf [ 2 ] * ( (  ) + 1 )
}

/**
 * 関数名 : get_MPU9250Accel
 * 引数 :  なし
 * 処理 : MPU9250から加速度を取得
 * 返り血 : なし
 */
float MPU9250AccelX , MPU9250AccelY , MPU9250AccelZ;  // 加速度G
void get_MPU9250Accel () {

    readI2C ( MPU9250 , 0x3B , 14 );  // 値を読み出す

    // 各軸のデータを生成
    int16_t ax = readI2Cbuf [ 0 ] << 8 | readI2Cbuf [ 1 ];
    int16_t ay = readI2Cbuf [ 2 ] << 8 | readI2Cbuf [ 3 ];
    int16_t az = readI2Cbuf [ 4 ] << 8 | readI2Cbuf [ 5 ];

    // 加速度に直す
    MPU9250AccelX = float ( ax ) * MPU9250AccelSensitiv;
    MPU9250AccelY = float ( ay ) * MPU9250AccelSensitiv;
    MPU9250AccelZ = float ( az ) * MPU9250AccelSensitiv;
}

/**
 * 関数名 : get_MPU9250Temp
 * 引数 :  なし
 * 処理 : MPU9250から内部温度を取得
 * 返り血 : MPU9250Temp : 温度deg
 */
float get_MPU9250Temp () {

    readI2C ( MPU9250 , 0x3B , 14 );  // 値を読み出す

    // 各軸のデータを生成
    int16_t t = readI2Cbuf [ 6 ] << 8 | readI2Cbuf [ 7 ];

    // 温度に直す
    float MPU9250Temp = float ( t ) / 333.87 + 21.0;

    return MPU9250Temp;  // 温度を返す
}


/**
 * 関数名 : get_MPU9250Gyro
 * 引数 :  なし
 * 処理 : MPU9250から角速度を取得
 * 返り血 : なし
 */
float MPU9250GyroX , MPU9250GyroY , MPU9250GyroZ;  // 角速度dps
void get_MPU9250Gyro () {

    readI2C ( MPU9250 , 0x3B , 14 );  // 値を読み出す

    // 各軸のデータを生成
    int16_t gx = readI2Cbuf [ 8 ] << 8 | readI2Cbuf [ 9 ];
    int16_t gy = readI2Cbuf [ 10 ] << 8 | readI2Cbuf [ 11 ];
    int16_t gz = readI2Cbuf [ 12 ] << 8 | readI2Cbuf [ 13 ];

    // 角速度に直す
    MPU9250GyroX = float ( gx ) * MPU9250GyroSensitiv;
    MPU9250GyroY = float ( gy ) * MPU9250GyroSensitiv;
    MPU9250GyroZ = float ( gz ) * MPU9250GyroSensitiv;
}

/**
 * 関数名 : get_AK8963Comp
 * 引数 :  なし
 * 処理 : MPU9250から地磁気を取得
 * 返り血 : なし
 */
float AK8963CompX , AK8963CompY , AK8963CompZ;  // 地磁気
void get_AK8963Comp () {

    readI2C ( AK8963 , 0x03 , 7 );  // 値を読み出す

    // 各軸のデータを生成
    int16_t cx = readI2Cbuf [ 1 ] << 8 | readI2Cbuf [ 0 ];
    int16_t cy = readI2Cbuf [ 3 ] << 8 | readI2Cbuf [ 2 ];
    int16_t cz = readI2Cbuf [ 5 ] << 8 | readI2Cbuf [ 4 ];

    // 磁気に直す
    AK8963CompX = float ( cx ) * AK8963CompX_Sensitiv;
    AK8963CompY = float ( cy ) * AK8963CompY_Sensitiv;
    AK8963CompZ = float ( cz ) * AK8963CompZ_Sensitiv;
}


/*****************
 * 3軸デジタル加速度センサI2C(ADXL345)
*****************/
// スレーブアドレス
// #define ADXL345_SDO_HIGH ( 0x1D )  // ADXL345スレーブアドレス(SDO=HIGH)
// #define ADXL345_SDO_LOW ( 0x53 )   // ADXL345スレーブアドレス(SDO=LOW)
#define ADXL345 ( 0x53 )           // ADXL345スレーブアドレス(SDO=LOW)

// ADXL345レジスタ類
#define ADXL345_DATA_FORMAT_ADDR ( 0x31 )  // データフォーマットのレジスタアドレス
#define ADXL345_POWER_CTL_ADDR ( 0x2D )    // パワーコントロールレジスタのアドレス
#define ADXL345_FIRST_DATA_ADDR ( 0x32 )   // 加速度データが格納されているレジスタの先頭

/**
 * 関数名 : setup_ADXL345_I2C
 * 引数 : なし
 * 処理 : 3軸加速度センサADXL345の初期設定(I2C通信)
 * 返り値 : なし
*/
void setup_ADXL345_I2C () {

    writeI2C ( ADXL345 , ADXL345_DATA_FORMAT_ADDR , 0x08 );  // データフォーマットの設定
    writeI2C ( ADXL345 , ADXL345_POWER_CTL_ADDR , 0x08 );    // 電源管理
}

/**
 * 関数名 : setup_ADXL345_I2C
 * 引数 : なし
 * 処理 : 3軸加速度センサADXL345の初期設定(I2C通信)
 * 返り値 : なし
*/
float ADXL345AccelXG , ADXL345AccelYG , ADXL345AccelZG;  // 加速度G
void get_ADXL345_I2C () {

    readI2C ( ADXL345 , ADXL345_FIRST_DATA_ADDR , 6 );  // 値を読み込む

    // 各軸のデータに直す
    int16_t x = readI2Cbuf [ 1 ] << 8 | readI2Cbuf [ 0 ];
    int16_t y = readI2Cbuf [ 3 ] << 8 | readI2Cbuf [ 2 ];
    int16_t z = readI2Cbuf [ 5 ] << 8 | readI2Cbuf [ 4 ];

    // 加速度に直す
    ADXL345AccelXG = ( float ) x / pow ( 2 , 8 );
    ADXL345AccelYG = ( float ) y / pow ( 2 , 8 );
    ADXL345AccelZG = ( float ) z / pow ( 2 , 8 );
}


/*****************
 * 3軸デジタル加速度センサSPI(ADXL345)
*****************/

// ADXL345スレーブ識別ピン
#define ADXL345_SS 10

/**
 * 関数名 : setup_ADXL345_SPI
 * 引数 : ss : スレーブ識別ピン
 * 処理 : 3軸加速度センサADXL345の初期設定(SPI通信)
 * 返り値 : なし
*/
void setup_ADXL345_SPI ( int ss ) {

    // 測定レンジの設定
    writeSPI ( ss , ADXL345_DATA_FORMAT_ADDR , 0x08 );  // 測定レンジ +-2g，烏賊同じ
    // POWER_TCL(節電機能の設定)
    writeSPI ( ss , ADXL345_POWER_CTL_ADDR , 0x08 );    // 測定モード，烏賊同じ
}

/**
 * 関数名 : get_ADXL345_SPI
 * 引数 : ss : スレーブ識別ピン
 * 処理 : 3軸加速度センサADXL345から加速度を取得
 * 返り値 : なし
*/
float ADXL345AccelXG , ADXL345AccelYG , ADXL345AccelZG;  // 加速度G
void get_ADXL345_SPI ( int ss ) {

    readSPI ( ss , ADXL345_FIRST_DATA_ADDR , 6 );  // 加速度データを読み込み

    // 各軸のデータに直す
    int16_t x = ( ( int16_t ) readSPIbuf [ 1 ] << 8 ) | readSPIbuf [ 0 ];
    int16_t y = ( ( int16_t ) readSPIbuf [ 3 ] << 8 ) | readSPIbuf [ 2 ];
    int16_t z = ( ( int16_t ) readSPIbuf [ 5 ] << 8 ) | readSPIbuf [ 4 ];

    // 加速度Gに直す
    ADXL345AccelXG = x / pow ( 2 , 8 );
    ADXL345AccelYG = y / pow ( 2 , 8 );
    ADXL345AccelZG = z / pow ( 2 , 8 );
}
