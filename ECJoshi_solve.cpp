// ECJoshi_solve.cpp 
// https://paiza.jp/poh/ec-campaign/
//
//・やったこと
//	1.入力データが大量であってもある程度速く捌けるように探索範囲をきっちり枝刈り
//	2.入力データをテキストファイルに差し替えて、検証を行いやすくした
//
//・やっていないこと
//	1.例外処理
//	2.詳細なコメント
//	3.可読性を損ないそうな最適化
// 
//・やるか迷ったこと
//	1.vectorのreserve()

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
class CampaignData{
public:
	bool ReadData(std::istream &input);
	void WriteData()const;
	void Solve();
	void Print()const;
	CampaignData(){};
	~CampaignData(){};
private:
	int day_num;
	int item_num;
	std::vector<int> item_prices;
	std::vector<int> day_price_targets;
	std::vector<int> results;

};
//引数のソートしたvectorの中から2個を選んでtargetに一番近い組み合わせの足し算結果を返す
//今回の問題の本質的な部分
int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array);

//キャンペーン日数分だけDPする
void CampaignData::Solve(){
	//まずは降順に並び替え
	std::sort(item_prices.begin(),item_prices.end(),std::greater<int>());
	for(unsigned int i=0; i<day_price_targets.size();i++){
		int currentday_result=SolveDPFromSortedArray( day_price_targets[i],item_prices);
		results.push_back(currentday_result);
	//std::cout<<"solve:"<<day_price_targets[i]<<"  result: "<<results[i]<<std::endl;
	}
	
return;
}

//探索を早くする
int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array){
//ペアのうち、大きい方をleft,小さい方をrightとする.left>=rightである
//sort済の配列は　最大....対象....対象の半分.....最小　の順に並んでいる
//pair_max_leftは対象-1の場所を指し、pair_min_leftは対象の半分-1の場所を指す
//left側のfor分は上記2点の間にあることが自明(pair_min_leftではなく、end-1だとワーストケースのループ回数が増える)
	int result=0;
	std::vector<int>::iterator pair_max_left=std::upper_bound(sorted_array.begin(), sorted_array.end(),target, std::greater<int>());
	//early return
	if(pair_max_left==sorted_array.end()){return result;}
 
	std::vector<int>::iterator pair_min_left=std::upper_bound(sorted_array.begin(), sorted_array.end(),target*0.5, std::greater<int>());

	if(pair_min_left==sorted_array.end()){
		pair_min_left--;
	}

	for (std::vector<int>::iterator it = pair_max_left; it != pair_min_left; ++it) {
            std::vector<int>::iterator it2 = std::lower_bound(it + 1, sorted_array.end(),target - *it,std::greater<int>());
            if (it2 != sorted_array.end() && result < *it + *it2) {
                result = *it + *it2;
				if (result == target) {
					return result;
                }
            }
        }

return result;
}

//結果を出力する。
void CampaignData::WriteData()const{
	//std::for_each(results.begin(), results.end(), [](int n) { std::cout << n << std::endl; });
	for(unsigned int i=0; i<results.size();i++){
		std::cout<<results[i]<<std::endl;
	}
	return;
};

//入力ストリームから書式に従ってデータを読み込む。
//引数でistreamを取ることで標準入力だけでなく、テストする時にファイル入力と切り替えられる
bool CampaignData::ReadData(std::istream &input){

	input >> item_num >> day_num;
	
	//ここで1行目のパースが終わったので入力が途切れるか
	//1行目のパース結果分のデータを受け取り終わるまで読み込みを続ける
	std::string current_line;
//	std::getline(input,current_line);
	item_prices.reserve(item_num);
	results.reserve(day_num);
	int line_counter=0;
	while(1){
		
		int tmp=0;
		input>>tmp;
		//読み込んだ1行の数字が商品の値段か、キャンペーンの価格かを振り分ける
		if(line_counter<item_num){
			item_prices.push_back(tmp);
		}else{
			day_price_targets.push_back(tmp);
		}
		line_counter++;
		if(line_counter>=(item_num+day_num)){break;}
	}

	return true;
};


//デバッグする時に入力の中身を表示する関数
void CampaignData::Print()const{
std::cout<<"1stLINE Parse Result item_num:"<<item_num<<" day_num:"<<day_num<<std::endl;
for(unsigned int i=0;i<item_prices.size();i++){
	std::cout<<item_prices[i]<<std::endl;
}
std::cout<<"Inputed item no:"<<item_prices.size()<<"  day_num:"<<day_price_targets.size()<<std::endl;
for(unsigned int j=0;j<day_price_targets.size();j++){
	std::cout<<day_price_targets[j]<<std::endl;
}	
std::cout<<"Print() Finish"<<std::endl;
return;
}



int main()
{
	std::cin.tie(0); 
	std::ios::sync_with_stdio(false); // Cのstdioとの同期をしない
	
	CampaignData campaigndata;
	
// READ_FROM_FILE
	/*
	std::ifstream ifs( "testdata.txt" );
	campaigndata.ReadData(ifs);
	campaigndata.Print();
	*/
	campaigndata.ReadData(std::cin);
	campaigndata.Solve();
	campaigndata.WriteData();
	return 0;
}

