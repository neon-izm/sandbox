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


int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array){
//ペアのうち、大きい方をleft,小さい方をrightとする.left>=rightである

int pair_max_left=0;
int pair_min_left=0;
int index_max=sorted_array.size()-1;
//枝刈り用の初期値検索。targetより大きい数は除外する。また、2個を選ぶうち、明らかに小さな2個を選ばないように調べている
while(1){
	if(index_max<=pair_max_left){
		pair_max_left=index_max;
		pair_min_left=index_max;
		break;
	} 
	if(index_max<=pair_min_left){
		pair_min_left=index_max;
		break;}

	if(sorted_array[pair_max_left]>target ){
		pair_max_left++;
	}
	if(sorted_array[pair_min_left]*2>=target ){
		pair_min_left++;
	}else{
	break;
	}
}

//ここまでで明らかに無駄な部分を省いた実質的なスタートインデックス、及び終端のインデックスが求まった
int result=0;
for(int left=pair_max_left; left<pair_min_left; left++){
	int right=pair_min_left;
	while(right<=index_max){
		int t=sorted_array[left]+sorted_array[right];
		//early return
		if(t==target ){
		return t;
		}
		else if(t<target && t>result){
		result=t;
		break;
		}
		right++;
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
	std::getline(input,current_line);
	item_prices.reserve(item_num);
	int line_counter=0;
	while(std::getline(input,current_line)){
		
		int tmp=std::atoi(current_line.c_str());
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

