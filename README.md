# 概要
Outline Extractorは自動発泡スチロールカッター向けに開発している輪郭線抽出プログラムです。  
ライブラリはOpenSiv3Dに依存しています。  

# ビルド
Visual StudioとOpenSiv3D(v0.4.0)をインストールしてください。  
レポジトリをクローンした後、ビルドを行ってください。  

# 他のプロジェクトでの利用法
OutlineDetector.hとOutlineDetector.cppを該当プロジェクトに導入する。
OutlineDetector.hをincludeしてください。

# リファレンス
## `OutlineDetector::OutlineDetector()`
コンストラクタにImageを代入することで内部で輪郭線抽出が始まります。  
デフォルトでは、grayscale() > 0.5が色分けの条件です。

## `OutlineDetector::GetOutlines()`
内部に保存されているOutlinesを得ることが出来ます。
