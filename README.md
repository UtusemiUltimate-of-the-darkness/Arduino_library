# Arduino_library

<div>
    Arduino自作ライブラリだよ．
</div>

<div>
<h3>できること</h3>
    <ul>
        <li>
            I2C通信読み書き
        </li>
        <li>
            SPI通信の初期化，読み書き
        </li>
        <li>
            9軸センサ(MPU9250)の加速度，角速度，コンパス，温度の取得(I2C/SPI)
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
    </ul>
</div>
