#include<algorithm>
#include<fstream>
#include"VerticalSerial.h"
#include<iostream>
#include<string>
#include"cxover.h"
#include<assert.h>

//#include"public_class_v3.h"
using namespace std;

vector<string> table;
struct PAIR{
    int m;
    int n;
};


void search(PaWithGFD PwithGFD);
void implication();
vector<PAIR> match(Pattern BG, Pattern SG);
void my_strcpy(char *dest, const char *src);

void init(){
    cout<<"nnew"<<endl;
    ofstream outFile("testout.txt");
    FILE * v_file;
    FILE * e_file;
    v_file = fopen("testV.txt", "r");
    e_file = fopen("testE.txt", "r");
	while(true){
        int id;
        int lable;
        vector<string> attributes;
        if(fscanf(v_file, "%d%d", &id, &lable) == EOF){
            break;
        }
        string tempStr = "";
        while(true){
            int flag = 0;
            char tempChar;
            fscanf(v_file, "%c", &tempChar);
            if(tempChar == '"'){
                if(flag == 1){
                    flag = 0;
                }
                else {
                    flag = 1;
                }
            }
            if(tempChar == '\n'){
                if(tempStr != "" && tempStr != "-"){
                    attributes.push_back(tempStr);
                }
                tempStr = "";
                break;
            }
            else if((tempChar == '\t' || tempChar == '	')){
                if(tempStr != "" && tempStr != "-"){
                    attributes.push_back(tempStr);
                }
                tempStr = "";
            }
            else {
                tempStr = tempStr + tempChar;
            }
        }

        V tempV(id, lable);
        for(int j = 0; j < attributes.size(); j++){
            tempV.addAttribute("<" + to_string(j) + ">", attributes[j]);
        }
        G_V.push_back(tempV);
	}
	cout<<"###############################"<<endl;
    fclose(v_file);
	while(true){
        int lable;
        int st_id;
        int dst_id;
        vector<string> attributes;
        if(fscanf(e_file, "%d%d%d", &st_id, &dst_id, &lable) == EOF){
            break;
        }

        E temp_E(lable, st_id, dst_id);
        G_V[st_id].addNeighbour_to(dst_id, temp_E);
        G_V[dst_id].addNeighbour_from(st_id, temp_E);

	}
}


int main(){
    init();
/*
    V v0(0, 0);
	V v1(1, 1);
	V v2(2, 2);
	V v3(3, 0);
	V v4(4, 1);
	V v5(5, 2);
	E e0(3, v0.getId(), v1.getId());
	E e1(3, v0.getId(), v2.getId());
	E e2(3, v1.getId(), v3.getId());
	E e3(3, v3.getId(), v4.getId());
	E e4(3, v3.getId(), v5.getId());
	Match match1(2, 1);
	Match match2(2, 1);
	Match match3(2, 1);
	Match match4(2, 1);
	Match match5(2, 1);
	v0.addAttribute("name", "a");
	v1.addAttribute("name", "a");
	v2.addAttribute("name", "c");
	v3.addAttribute("name", "a");
	v4.addAttribute("name", "a");
	v5.addAttribute("name", "c");
	match1.addV(v0);
	match1.addV(v1);
	match1.addE(e0);
	match1.setPivot(0);
	match2.addV(v0);
	match2.addV(v2);
	match2.addE(e1);
	match2.setPivot(0);
	match3.addV(v1);
	match3.addV(v3);
	match3.addE(e2);
	match3.setPivot(1);
	match4.addV(v3);
	match4.addV(v4);
	match4.addE(e3);
	match4.setPivot(3);
	match5.addV(v3);
	match5.addV(v5);
	match5.addE(e4);
	match5.setPivot(3);
	Pattern pattern2(2, 1);
	pattern2.addMatch(match1);
	pattern2.addMatch(match2);
	pattern2.addMatch(match3);
	pattern2.addMatch(match4);
	pattern2.addMatch(match5);//上述初始化为垂直扩展部分已得数据
	//##########################################################
	vector<Pattern> patterns;
	patterns.push_back(pattern2);



    vector<GFD> gfds = cxover(patterns);*/
    VerticalSerial vtS;

    vtS.vertical_serial(1);			//生成2个点的match
    vector<Pattern> Patterns1 = vtS.getPatterns();
    vtS.setLastMatches(vtS.getNowMatches());
    vtS.setLastPatterns(vtS.getPatterns());
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    vector<GFD> gfds2 = cxover(Patterns1);
    cout << Patterns1.size() <<endl;

    cout << "--------now n=1 is over-------"<<endl;

  	vtS.vertical_serial(2);			//生成3个点的match
	vector<Pattern> Patterns2 = vtS.getPatterns();
	vtS.setLastMatches(vtS.getNowMatches());
	vtS.setLastPatterns(vtS.getPatterns());
	vector<GFD> gfds3 = cxover(Patterns2);
	cout << Patterns2.size() <<endl;

	cout << "--------now n=2 is over-------"<<endl;

  	vtS.vertical_serial(3);			//生成4个点的match
	vector<Pattern> Patterns3 = vtS.getPatterns();
	vtS.setLastMatches(vtS.getNowMatches());
	vtS.setLastPatterns(vtS.getPatterns());
	vector<GFD> gfds4 = cxover(Patterns3);
	cout << Patterns3.size() <<endl;

	cout << "--------now n=3 is over-------"<<endl;

  	vtS.vertical_serial(4);			//生成5个点的match
	vector<Pattern> Patterns4 = vtS.getPatterns();
	vtS.setLastMatches(vtS.getNowMatches());
	vtS.setLastPatterns(vtS.getPatterns());
	cout << Patterns4.size() <<endl;

	cout << "--------now n=4 is over-------"<<endl;
	implication();
}




//PwithGFD.getGFDs()[0].getY //看看这个在table里有没有，有的话就把这个gfd erase掉
void implication()
{
	cout << "------------now implication-----------" << endl;
	int leaf = pot[5];//5个点的pattern作为最后一层时，第一个pattern的位置
	int leaf_max = PwithGFDs.size();
	for (int i = leaf; i < leaf_max;i++)//遍历叶子结点的package
	{
		search(PwithGFDs[i]);
		search(PwithGFDs[PwithGFDs[i].getFaId()]);
		search(PwithGFDs[PwithGFDs[PwithGFDs[i].getFaId()].getFaId()]);
		search(PwithGFDs[PwithGFDs[PwithGFDs[PwithGFDs[i].getFaId()].getFaId()].getFaId()]);
		cout << "aksd";
		for(int y=0;y<PwithGFDs[i].getGFDs().size();y++)
		{
			for (vector<string>::iterator iter = table.begin();iter != table.end(); ++iter)
			{
				/************************************************/
				if(PwithGFDs[i].getGFDs()[y].getY() == *iter)
				{
					int yu = 0;
					for (vector<GFD>::iterator iter2 = PwithGFDs[i].getGFDs().begin();; ++iter2, yu++)
					{
						if(yu==y)
						{
							iter2 = PwithGFDs[i].getGFDs().erase(iter2);
						}
					}
					
				}
					
			}
		}
	}



}
vector<string> TABLE;
void search(PaWithGFD PwithGFD)//match为开始的两点遍历
{
	cout << "------------now start search-----------" << endl;
	vector<PAIR> pair;
	int BG_count ;
    int SG_count ;
	pair=match(PwithGFD.getNowPattern(), PwithGFDs[PwithGFD.getFaId()].getNowPattern());//把gfds的literial都加到TABLE里
	TABLE = PwithGFDs[PwithGFD.getFaId()].getNowPattern().getLiteral();//一层pattern的所有的东西
	for (int j = 0; j < TABLE.size();j++)
	{
		char *Literial;
		string mm;
		string temp;
		int flag1=0;
		my_strcpy(Literial,TABLE[j].c_str());
		for (int m = 0; m < sizeof(Literial);m++)
		{
			int n = 0;
			while (Literial[n]!='\0')
			{
				while (Literial[n] != '.')
				{
					mm = mm + Literial[n];
					n++;
				}
				for (vector<PAIR>::iterator iter = pair.begin();iter != pair.end(); ++iter)
				{
					if(to_string(iter->m)==mm)
					{
						mm = to_string(n);
						break;
					}
				}
				temp = temp + mm;
				while (Literial[n] != '.'){
					flag1 = 1;
				}
				if(flag1==1)//x.a=y.b
				{
					while(Literial[n] != '=')
					{
						temp = temp + Literial[n];
						n++;
					}
					temp = temp + Literial[n];
					mm.clear();
					while(Literial[n] != '.')
					{
						mm =mm+ Literial[n];
						n++;
					}
					for (vector<PAIR>::iterator iter = pair.begin();iter != pair.end(); ++iter)
					{
						if(to_string(iter->m)==mm)
						{
							mm = to_string(n);
							break;
						}
					}
					temp = temp + Literial[n];
					mm.clear();
					while(Literial[n] != '\0')
					{
						temp = temp + Literial[n];
					}
				}
				else//x.a=c
					while(Literial[n] != '\0')
					{
						temp = temp + Literial[n];
					}
				flag1 = 0;
			}
			table.push_back(temp);
			temp.clear();
		}
		//按照TABLE去找pair然后替换加入table
	}
	//TABLE清零
	TABLE.clear();
	//pair清零
	pair.clear();
}



void my_strcpy(char *dest,const char *src)
{
	while('\0'!= *src)
	{
		assert(src);
		assert(dest);
 
		*dest=*src;
		src++;
		dest++;
	}
	*dest='\0';
}


vector<PAIR> match(Pattern BG,Pattern SG)
{
	vector<PAIR> temp_pair;
	PAIR Pair;
	for (int i = 0; i < BG.getSetE().size();i++)
	{
		int temp = i;
		int j = 0;
		int flag = 0;
		while(j!=SG.getSetE().size())
		{
			if(BG.getSetE()[temp].getLable()==SG.getSetE()[j].getLable()&&BG.getSetE()[temp].getSt())
			{
				for (vector<V>::iterator iter = BG.getSetV().begin();iter != BG.getSetV().end(); ++iter)
				{
					for (vector<V>::iterator iter1 = SG.getSetV().begin();iter1 != SG.getSetV().end(); ++iter1)
					{
						if(iter->getLable()==iter1->getLable())
						{
							flag = 1;
							Pair.m = iter->getId();
							Pair.n = iter1->getId();
							temp_pair.push_back(Pair);
						}
							
					}
					
				}
				if(flag==0)
					break;
				flag = 0;
				temp++;
				j++;
			}
			else
				break;
		}

	}
}
