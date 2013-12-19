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

//�T���𑁂�����
int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array){
//�y�A�̂����A�傫������left,����������right�Ƃ���.left>=right�ł���
//sort�ς̔z��́@�ő�....�Ώ�....�Ώۂ̔���.....�ŏ��@�̏��ɕ���ł���
//pair_max_left�͑Ώ�-1�̏ꏊ���w���Apair_min_left�͑Ώۂ̔���-1�̏ꏊ���w��
//left����for���͏�L2�_�̊Ԃɂ��邱�Ƃ�����(pair_min_left�ł͂Ȃ��Aend-1���ƃ��[�X�g�P�[�X�̃��[�v�񐔂�������)
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
//	std::getline(input,current_line);
	item_prices.reserve(item_num);
	results.reserve(day_num);
	int line_counter=0;
	while(1){
		
		int tmp=0;
		input>>tmp;
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

