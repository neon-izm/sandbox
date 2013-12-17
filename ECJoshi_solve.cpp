// ECJoshi_solve.cpp 
// https://paiza.jp/poh/ec-campaign/
//
//�E���������
//	1.���̓f�[�^����ʂł����Ă�������x�����J����悤�ɒT���͈͂���������}����
//	2.���̓f�[�^���e�L�X�g�t�@�C���ɍ����ւ��āA���؂��s���₷������
//
//�E����Ă��Ȃ�����
//	1.��O����
//	2.�ڍׂȃR�����g
//	3.�ǐ��𑹂Ȃ������ȍœK��
// 
//�E��邩����������
//	1.vector��reserve()

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
//�����̃\�[�g����vector�̒�����2��I���target�Ɉ�ԋ߂��g�ݍ��킹�̑����Z���ʂ�Ԃ�
//����̖��̖{���I�ȕ���
int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array);

//�L�����y�[������������DP����
void CampaignData::Solve(){
	//�܂��͍~���ɕ��ёւ�
	std::sort(item_prices.begin(),item_prices.end(),std::greater<int>());
	for(unsigned int i=0; i<day_price_targets.size();i++){
		int currentday_result=SolveDPFromSortedArray( day_price_targets[i],item_prices);
		results.push_back(currentday_result);
	//std::cout<<"solve:"<<day_price_targets[i]<<"  result: "<<results[i]<<std::endl;
	}
	
return;
}


int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array){
//�y�A�̂����A�傫������left,����������right�Ƃ���.left>=right�ł���

int pair_max_left=0;
int pair_min_left=0;
int index_max=sorted_array.size()-1;
//�}����p�̏����l�����Btarget���傫�����͏��O����B�܂��A2��I�Ԃ����A���炩�ɏ�����2��I�΂Ȃ��悤�ɒ��ׂĂ���
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

//�����܂łŖ��炩�ɖ��ʂȕ������Ȃ��������I�ȃX�^�[�g�C���f�b�N�X�A�y�яI�[�̃C���f�b�N�X�����܂���
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

//���ʂ��o�͂���B
void CampaignData::WriteData()const{
	//std::for_each(results.begin(), results.end(), [](int n) { std::cout << n << std::endl; });
	for(unsigned int i=0; i<results.size();i++){
		std::cout<<results[i]<<std::endl;
	}
	return;
};

//���̓X�g���[�����珑���ɏ]���ăf�[�^��ǂݍ��ށB
//������istream����邱�ƂŕW�����͂����łȂ��A�e�X�g���鎞�Ƀt�@�C�����͂Ɛ؂�ւ�����
bool CampaignData::ReadData(std::istream &input){

	input >> item_num >> day_num;
	
	//������1�s�ڂ̃p�[�X���I������̂œ��͂��r�؂�邩
	//1�s�ڂ̃p�[�X���ʕ��̃f�[�^���󂯎��I���܂œǂݍ��݂𑱂���
	std::string current_line;
	std::getline(input,current_line);
	item_prices.reserve(item_num);
	int line_counter=0;
	while(std::getline(input,current_line)){
		
		int tmp=std::atoi(current_line.c_str());
		//�ǂݍ���1�s�̐��������i�̒l�i���A�L�����y�[���̉��i����U�蕪����
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


//�f�o�b�O���鎞�ɓ��͂̒��g��\������֐�
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
	std::ios::sync_with_stdio(false); // C��stdio�Ƃ̓��������Ȃ�
	
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

