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

class CampaignData{
public:
	bool ReadData(std::istream &input);
	void WriteData()const;
	void Solve();
	void Print()const;
private:
	int day_num;
	int item_num;
	std::vector<int> item_prices;
	std::vector<int> day_price_targets;
	std::vector<int> results;

	bool ParseFirstLine(const std::string &line);
};
//�����̃\�[�g����vector�̒�����2��I���target�Ɉ�ԋ߂��g�ݍ��킹�̑����Z���ʂ�Ԃ�
//����̖��̖{���I�ȕ���
int SolveDPFromSortedArray(const int target,std::vector<int> &sorted_array);

//�L�����y�[������������DP����
void CampaignData::Solve(){
	//�܂��͍~���ɕ��ёւ�
	std::sort(item_prices.begin(),item_prices.end(),std::greater<int>());
	for(int i=0; i<day_price_targets.size();i++){
		int currentday_result=SolveDPFromSortedArray( day_price_targets[i],item_prices);
		results.push_back(currentday_result);
	//std::cout<<"solve:"<<day_price_targets[i]<<"  result: "<<result[i]<<std::endl;
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
	if(index_max<=pair_max_left || index_max<=pair_min_left){break;}

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
for(int left=pair_max_left; left<=pair_min_left; left++){
	for(int right=pair_min_left; right<=index_max; right++){
		int t=sorted_array[left]+sorted_array[right];
		//early return
		if(t==target){
		return t;
		}
		else if(t<target && t>result){
		result=t;
		}
	}
}
return result;
}

//���ʂ��o�͂���B
void CampaignData::WriteData()const{
	std::for_each(results.begin(), results.end(), [](int n) { std::cout << n << std::endl; });
	return;
};

//���̓X�g���[�����珑���ɏ]���ăf�[�^��ǂݍ��ށB
//������istream����邱�ƂŕW�����͂����łȂ��A�e�X�g���鎞�Ƀt�@�C�����͂Ɛ؂�ւ�����
bool CampaignData::ReadData(std::istream &input){
	std::string current_line;
	std::getline(input,current_line);
	
	bool parseok=ParseFirstLine(current_line);
	if(parseok==false){return false;}
	//������1�s�ڂ̃p�[�X���I������̂œ��͂��r�؂�邩
	//1�s�ڂ̃p�[�X���ʕ��̃f�[�^���󂯎��I���܂œǂݍ��݂𑱂���
	int line_counter=0;
	while(std::getline(input,current_line)){
		if(current_line.empty() ){break;}
		
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

//�ǂݍ��݊֐��̂����A��s�ڂ�������ȏ����Ȃ̂Ő�p�̊֐���݂���
bool CampaignData::ParseFirstLine(const std::string &line){
	std::stringstream buf(line);
	std::string day_s,item_num_s;
	if(buf>>item_num_s && buf>>day_s){
		item_num= std::atoi(item_num_s.c_str());
		day_num= std::atoi(day_s.c_str());
	}
	else{return false;}

	return true;
}


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

/*	testdata.txt
4 3�@ 
8000 
4000 
9000
6000
3000 
14000 
10000 
*/
//�璷�����A�e�X�g�R�[�h�̗������
void TESTCODE(std::string filename="testdata.txt"){
		
	CampaignData campaigndata;
	std::ifstream ifs( "testdata.txt" );
	campaigndata.ReadData(ifs);
	campaigndata.Print();
	campaigndata.Solve();
	campaigndata.WriteData();
	return;
}



int main(int argc, char* argv[])
{
//�t�@�C������ǂ�ł݂�ꍇ�̓R�����g����
//#define READ_FROM_FILE 
	
	CampaignData campaigndata;
#ifdef READ_FROM_FILE
	std::ifstream ifs( "testdata.txt" );
	campaigndata.ReadData(ifs);
#else
	campaigndata.ReadData(std::cin);
#endif
	campaigndata.Solve();
	campaigndata.WriteData();
	return 0;
}
