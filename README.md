# Arduino_library

<div>
    Arduino自作関数まとめたよ．
</div>

<div>
<h3>できること</h3>
    <ul>
        <li>
            I2C通信の初期化，読み書き
        </li>
        <li>
            SPI通信の初期化，読み書き
        </li>
        <li>
            9軸センサ ( MPU9250 ) での加速度，角速度，コンパス，温度の取得 ( I2C )
        </li>
        <li>
            3軸加速度センサ ( ADXL345 ) での加速度取得 ( I2C / SPI )
        </li>
        <li>
            3軸加速度センサ ( ADXL312 ) での加速度取得 ( I2C )
        </li>
        <li>
            アナログ温度センサ ( LM61BIZ ) での温度取得
        </li>
        <li>
            アナログ温度センサ ( LM35 ) での温度取得
        </li>
        <li>
            アナログ湿度センサ ( HIH4030 ) での湿度取得
        </li>
        <li>
            CdSセル ( 暗抵抗1MΩ ) での照度取得
        </li>
        <li>
            測距センサ ( GP2Y0A21YK ) での距離取得
        </li>
    </ul>
</div>

<div>
    <h3>バージョン履歴</h3>
    <ul>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v0.0.0">version 0.0.0</a></h4>
            <div>
                <ul>
                    <li>
                        9軸センサ(MPU9250)の加速度取得関数作成
                    </li>
                    <li>
                        9軸センサ(MPU9250)の温度取得関数作成
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v0.0.1">version 0.0.1</a></h4>
            <div>
                <ul>
                    <li>
                        I2C通信読み出した値を返り値とする関数作成
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.0.0">version 1.0.0</a></h4>
            <div>
                <ul>
                    <li>
                        I2C読み出し関数複数バイトの読み出しに対応
                    </li>
                    <li>
                        9軸センサ(MPU9250)のレジスタ類，レンジのアドレスをマクロ定義
                    </li>
                    <li>
                        加速度，角速度，コンパス，温度取得関数記述
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.1.0">version 1.1.0</a></h4>
            <div>
                <ul>
                    <li>
                        SPI通信の初期化，読み書き関数の追加
                    </li>
                    <li>
                        9軸センサ(MPU9250)の加速度，角速度，コンパス，温度をI2C，SPI通信で取得可能
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.2.0">version 1.2.0</a></h4>
            <div>
                <ul>
                    <li>
                        serialEvent関数の追加
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.2.1">version 1.2.1</a></h4>
            <div>
                <ul>
                    <li>
                        SPI通信初期化関数の引数にスレーブセレクトピン追加
                    </li>
                    <li>
                        コードの整理で可読性の向上
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.3.0">version 1.3.0</a></h4>
            <div>
                <ul>
                    <li>
                        SPI通信初期化関数の引数のスレーブセレクトピン除外
                    </li>
                    <li>
                        SPI通信での信号ピンをマクロで定義
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.4.0">version 1.4.0</a></h4>
            <div>
                <ul>
                    <li>
                        9軸センサ(MPU9250)の温度取得関数の返り値設定
                    </li>
                    <li>
                        3軸加速度センサ(ADXL345)でのSPI通信用関数追加
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.5.0">version 1.5.0</a></h4>
            <div>
                <ul>
                    <li>
                        3軸加速度センサ(ADXL345)I2C通信用関数追加
                    </li>
                    <li>
                        シリアルモニタ初期化関数の除外
                    </li>
                    <li>
                        3軸加速度センサ(ADXL345)加速度算出式の改良
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.5.1">version 1.5.1</a></h4>
            <div>
                <ul>
                    <li>
                        マージ不能のため新ブランチ作成
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.6.0">version 1.6.0</a></h4>
            <div>
                <ul>
                    <li>
                        9軸センサ(MPU-9250)の地磁気測定モードの指定
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v1.6.1">version 1.6.1</a></h4>
            <div>
                <ul>
                    <li>
                        9軸センサ各センサ感度記述法改良
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v2.0.0">version 2.0.0</a></h4>
            <div>
                <ul>
                    <li>
                        各センサ毎にファイル分け
                    </li>
                    <li>
                        アナログ温度センサ ( LM61BIZ ) の追加
                    </li>
                    <li>
                        アナログ湿度センサ ( HIH4030 ) の追加
                    </li>
                    <li>
                        CdSセルの追加
                    </li>
                </ul>
            </div>
        </li>
        <li>
            <h4><a href="https://github.com/UtusemiUltimate-of-the-darkness/Arduino_library/tree/v2.1.0">version 2.1.0</a></h4>
            <div>
                <ul>
                    <li>
                        3軸加速度センサ ( ADXL312 ) の追加
                    </li>
                    <li>
                        アナログ測距センサ ( GP2Y0A21YK ) の追加
                    </li>
                    <li>
                        アナログ温度センサ ( LM35 ) の追加
                    </li>
                </ul>
            </div>
        </li>
    </ul>
</div>
