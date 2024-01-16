# cpp-03-project-ja

## 必要なソフトウェア
FLTKのバージョン1.3.9を使用してください。開発する際は[FLTKのドキュメント](https://www.fltk.org/doc-1.3)を参照してください。

### Windows (MSYS2を使用) の場合
FLTKのインストール:
```
pacman -S mingw-w64-ucrt-x86_64-fltk
```

プロジェクトのビルドと実行:
```
g++ -std=c++17 -o image_processor main.cpp -l fltk_images `fltk-config --cxxflags --ldflags`
./image_processor
```

### Macの場合
FLTKのインストール:
```
brew install fltk
```

プロジェクトのビルドと実行:
```
g++ -std=c++17 -o image_processor main.cpp -l fltk_images -l fltk_jpeg `fltk-config --cxxflags --ldflags`
./image_processor
```
