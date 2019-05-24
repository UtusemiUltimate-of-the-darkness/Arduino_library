/**
 * ファイル名: Arudino_library.ino
 * 作成者: 命を燃やせない死んでない闇の空蝉ultimate
 * 最終更新日: 2019-3-22
 * バージョン: 0.0.1
 *
 * 機能
 *   通信系
 *     I2C R/W
 *   センサ系
 *     MPU-9250
 *
 * 更新履歴
 *   v0.0.0
 *     9軸センサ(MPU9250)の加速度，温度を取得する
 *   v0.0.1
 *     I2C通信読み出す際の一時格納データを返り血とした．
 */
#include < Wire.h >
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
 * 引数 : DEVICE_ADDR : スレーブデバイスアドレス, REGISTER_ADDR : 読み込む最初のレジスタアドレス, num : 読み込むバイト数
 * 処理 : 特定のスレーブデバイスから指定されたレジスタの値を読み込む
 * 返り血 : buffer : 読み出したデータ
 */
void readI2C ( byte DEVICE_ADDR , byte REGISTER_ADDR , int num ) {

    byte buffer [];

    Wire.beginTransmission ( DEVICE_ADDR );  // DEVICE_ADDRで指定したスレーブデバイスに送信処理を始める
    Wire.write ( REGISTER_ADDR );            // レジスタアドレスを書き込む(Wire.requestFrom()にかかる)
    Wire.endTransmission ();                 // スレーブデバイスに対する送信を完了(返り血あり)
    Wire.beginTransmission ( DEVICE_ADDR );  // DEVICE_ADDRで指定したスレーブデバイスに送信処理を始める
    Wire.requestFrom ( DEVICE_ADDR , num );  // DEVICE_ADDRのスレーブデバイスのREGISTER_ADDRからnumバイトデータを読む

    int i = 0;
    // スレーブデバイスからのデータを格納
    while ( Wire.available () ) {

        buffer [ i++ ] = Wire.read ();  // 読み出したデータを配列に格納
    }

    Wire.endTransmission ();  // スレーブデバイスに対する送信を完了(返り血あり)

    return buffer;  // 読み出したデータを返す
}

/**
 * 関数名 : writeI2C
 * 引数 : DEVICE_ADDR : スレーブデバイスアドレス, REGISTER_ADDR : 書き込むレジスタのアドレス, value : 書き込む値
 * 処理 : 特定のスレーブデバイスの指定されたレジスタに値を書き込む
 * 返り血 : なし
 */
void writeI2C ( uint8_t DEVICE_ADDR , uint8_t REGISTER_ADDR , uint8_t value ) {

    Wire.beginTransmission ( DEVICE_ADDR );  // DEVICE_ADDRで指定したスレーブデバイスに送信処理を始める
    Wire.write ( REGISTER_ADDR );            // レジスタアドレスを書き込む
    Wire.write ( value );                    // 送信するデータをキューに入れる
    Wire.endTransmission ();                 // スレーブデバイスに対する送信を完了(返り血あり)
}



/*****************
 * 9軸センサ(MPU-9260)
 *****************/
/**
 * 関数名 : getAccel
 * 引数 : なし
 * 処理 : 9軸センサから加速度データを取得し加速度Gに直す
 * 返り血 : なし
 */
void getAccel () {

    // 加速度データ格納変数
    int16_t xAxis = 0;  // X軸加速度データ(16bit)
    int16_t yAxis = 0;  // Y軸加速度データ(16bit)
    int16_t zAxis = 0;  // Z軸加速度データ(16bit)

    readI2C ( DEVICE_ADDR_ACCEL_GYRO , 0x3B , 14 , accelTempGyro_buffer );  // 加速度(角速度，温度)データ読み込み

    // 各軸の角速度データ
    xAxis = ( accelTempGyro_buffer [ 0 ] << 8 ) | accelTempGyro_buffer [ 1 ];  // X軸加速度データ
    yAxis = ( accelTempGyro_buffer [ 2 ] << 8 ) | accelTempGyro_buffer [ 3 ];  // Y軸加速度データ
    zAxis = ( accelTempGyro_buffer [ 4 ] << 8 ) | accelTempGyro_buffer [ 5 ];  // Z軸加速度データ

    // 加速度Gに直す(16bitなので2^15で割る)→(A/D変換値から電圧を求める場合と同じ考え方)
    accelXG = xAxis * accelRange / pow ( 2 , 15 );
    accelYG = yAxis * accelRange / pow ( 2 , 15 );
    accelZG = zAxis * accelRange / pow ( 2 , 15 );
}

/**
 * 関数名 : getTemp
 * 引数 : なし
 * 処理 : 9軸センサから温度データを取得し，度Cに直す
 * 返り血 : なし
 */
void getTemp () {

    int16_t temp = 0;  // 温度データ

    readI2C ( DEVICE_ADDR_ACCEL_GYRO , 0x3B , 14 , accelTempGyro_buffer );  // 温度(加速度，角速度)データ読み込み

    temp = ( accelTempGyro_buffer [ 6 ] << 8 ) | accelTempGyro_buffer [ 7 ];  // 読み込んだ温度データを変数に格納

    tempC = temp / 333.87 + 21.0;  // 温度Cに直す
}
