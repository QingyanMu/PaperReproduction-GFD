#include <iostream>
#include<map>
#include<vector>
#include<algorithm>
//#include"public_class_v1.h"
using namespace std;
/*
class E;

class V
{
	private:
		int real_id;//���Ψһ��ʶ
		int lable;//���lable
		//map<string, string> attribute;//������ԣ���Ϊ���Ե���������֣�ѧ��
		//vector<V> neighbour_V;//�õ���ڵ㼯��
		//vector<E> neighbour_E;//�õ�ı߼���,ֵΪ1��ʾ���ߣ�0��ʾ��õ�ı�
		vector<string> attribute_key;
		vector<string> attribute_value;
		vector<V> neighbour_V;
		vector<E> neighbour_E;
    public:
        V(int id, int lab){
			real_id = id;
			lable = lab;
		}

		void addAttribute(string key, string value) {
			attribute_key.push_back(key);
			attribute_value.push_back(value);
		}

		vector<string> getAttribute_key(){
			return attribute_key;
		}
		vector<string> getAttribute_value(){
			return attribute_value;
		}

		int getId(){
            return real_id;
		}

		int getLable(){
            return lable;
		}
};

class E
{
	private:
		int real_id;//�ߵ�Ψһ��ʶ
		int lable;//�ߵ�lable
		int st_v_id;//�ߵ���ʼ��
		int dst_v_id;//�ߵ��յ�

	public:
	    E(int lab,int st, int dst){
            lable = lab;
            st_v_id = st;
            dst_v_id = dst;
	    }

		void setId(int id){
			real_id = id;
		}

		int getId(){
			return real_id;
		}

		void setLable(int lab){
			lable = lab;
		}

		int getLable(){
			return lable;
		}


		int getSt() {
			return st_v_id;
		}

		int getDst() {
			return dst_v_id;
		}
};

class Match//ƥ��ͼ
{
	private:
	    int pivot_id;//��������ʵid
		int v_count;//��ĸ���
		int e_count;//�ߵĸ���
		int cnt;//������
		//unordered_map<int,V> set_v;//�㼯�ϣ�����id
		//vector<E> set_e;//�߼���
		//unordered_set<string> match_literal;//��ͼ�е�literal����,��ֱʱ�������
		vector<V> setV;
		vector<E> setE_value;
		vector<int> setE_st;
		vector<int> setE_dst;
		vector<string> match_literal;


	public:
		Match(int v_count, int e_count){
			v_count = v_count;
			e_count = e_count;
			cnt = 0;
		}

		void addV(V v){
			setV.push_back(v);
			cnt++;
		}

		void addE(E e){
			setE_value.push_back(e);
			for(int i = 0; i < setV.size(); i ++){
                if(setV[i].getId() == e.getDst()){
                    setE_dst.push_back(i);
                }
                else if(setV[i].getId() == e.getSt()){
                    setE_st.push_back(i);
                }
			}
		}
		vector<V> getSetV(){
			return setV;
		}
		vector<E> getSetE_value(){
			return setE_value;
		}
		vector<int> getSetE_dst(){
			return setE_dst;
		}
		vector<int> getSetE_st(){
			return setE_st;
		}
		void addLiteral(string literal){
			for(int i = 0; i < match_literal.size(); i ++){
                if(literal == match_literal[i]){
                    return;
                }
			}
			match_literal.push_back(literal);
		}

		vector<string> getLiteral(){
			return match_literal;
		}

		void setPivot(int pivot){
            pivot_id = privot;
		}

		int getPivot(){
            return pivot_id;
		}
};

class Pattern
{
	private:

		int v_count;//�����
		int e_count;//�߸���
		//unordered_set<Match> set_match;//��patternƥ�䵽��ͼ��
		//unordered_set<string> pattern_literal;//����ƥ��ͼ��literal����
		//vector<string> literal_up;//������ģ�����������
		vector<V> setV;
		vector<string> pattern_literal;
		vector<Match> setMatch;

	public:
		Pattern(int v_count, int e_count){
			v_count = v_count;
			e_count = v_count;
		}

		void addMatch(Match match){
			setMatch.push_back(match);
		}
		vector<Match> getMatch(){
			return setMatch;
		}
		void addLiteral(string literal){
			for(int i = 0; i < pattern_literal.size(); i ++){
                if(literal == pattern_literal[i]){
                    return;
                }
			}
			pattern_literal.push_back(literal);
		}
		vector<string> getLiteral(){
			return pattern_literal;
		}
};
*/
/*
class GFD
{
	private:
		//unordered_map<int,V> set_v;//GFD�е�ļ���,ֵΪ����id
		//vector set_e;//GFD�бߵļ���,ֵΪ�ߵ���ʼ����յ�ĳ���id
		//string Y;//Y��literal
		//vector<string> X;//X��literal����
		//int count_v;//�Ե���м�������ʼֵΪ0
		vector<int> privots;
		int support;
		vector<V> setV;
		vector<E> setE_value;
		vector<int> setE_st;
		vector<int> setE_dst;
		string Y;
		vector<string> X;

	public:
		GFD(vector<V> Vs, vector<E> Es_value,vector<int> Es_st, vector<int> Es_dst, string y, vector<string> x){
			setV = Vs;
			setE_value = Es_value;
			setE_st = Es_st;
			setE_dst = Es_dst;
			Y = y;
			X = x;
			support = 0;
		}

		void setY(string y) {
			Y = y;
		}

		vector<string> getX(){
            return X;
		}

		string getY(){
            return Y;
		}

		int getSupport(){
            return support;
		}

		void setSupport(int surp){
            support = surp;
		}

		void addSupport(){
            support = support + 1;
		}

		void setPrivots(vector<int> pvs){
            privots = pvs;
		}

		vector<int> getPrivots(){
            return privots;
		}

		void coutGFD(){
            for(int i = 0; i < setV.size(); i++){
                cout<<"v "<<i<<" "<<setV[i].getLable()<<" "<<setV[i].getAttribute_value()[0]<<endl;
            }
            for(int i = 0; i < setE_value.size(); i++){
                cout<<"e "<<setE_st[i]<<" "<<setE_value[i].getLable()<<" "<<setE_dst[i]<<endl;
            }
            cout<<"X: "<<X[0];
            for(int i = 1; i < X.size(); i ++){
                cout<<" && "<<X[i];
            }
            cout<<endl;
            cout<<"Y: "<<Y<<endl;
            cout<<"support: "<<support<<endl;
            cout<<endl;
		}
};
*/
int isSubset(vector<string> v1, vector<string> v2){
 int i=0,j=0;
 int m=v1.size();
 int n=v2.size();
 if(m<n){
  return 0;
 }
 sort(v1.begin(),v1.end());
 sort(v2.begin(),v2.end());
 while(i<n&&j<m){
  if(v1[j]<v2[i]){
   j++;
  }
  else if(v1[j]==v2[i]){
   j++;
   i++;
  }
  else if(v1[j]>v2[i]){
   return 0;
  }
 }
 if(i<n){
  return 0;
 }
 else{
  return 1;
 }
}

bool is_contain(vector<int> theList, int theIterm){
    for(int i=0; i < theList.size(); i ++){
        if(theList[i] == theIterm){
            return true;
        }
    }
    return false;
}

vector<GFD> cxover(vector<Pattern> patterns)
{
    vector<GFD> GFDs;
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
	pattern2.addMatch(match5);//������ʼ��Ϊ��ֱ��չ�����ѵ�����
	//##########################################################
	vector<Pattern> patterns;
	patterns.push_back(pattern2);*/
    for(int p = 0; p < patterns.size(); p++){
        vector<GFD> packet;
        vector<Match> matchs = patterns[p].getSetMatch();
        for(int i = 0;i < matchs.size();i++){//ÿ��ƥ��ͼ
            Match & match = matchs[i];
            for(int j = 0; j < match.getSetV().size(); j++){//ƥ��ͼ��ÿ����
                V j_v = match.getSetV()[j];
                vector<string> attribute_keys = j_v.getAttribute_key();
                vector<string> attribute_values = j_v.getAttribute_value();//���literal����

                if(attribute_keys.size() > 0){
                    for(int k = 0; k < attribute_values.size(); k++){//����ÿһ��literal
                        string literal = to_string(j) + ".";
                        literal = literal + attribute_keys[k] + "=" + attribute_values[k] + "[c]";
                        cout<<literal<<endl;
                        match.addLiteral(literal);
                    }

                    for(int k = 0; k < attribute_keys.size(); k++) {
                        string temp1 = attribute_values[k];//a,c
                        for(int l = j + 1; l < match.getSetV().size(); l++){
                            V l_v = match.getSetV()[l];
                            vector<string> attribute_keys0 = l_v.getAttribute_key();
                            vector<string> attribute_values0 = l_v.getAttribute_value();//���literal����
                            for(int m = 0; m < attribute_keys0.size(); m++) {
                                string temp2 = attribute_values0[m];
                                if(temp1 == temp2){
                                    string literal = to_string(j) + "." + attribute_keys[k] + "=" + to_string(l) + "." + attribute_keys0[m] + "[v]";
                                    match.addLiteral(literal);
                                }
                            }
                        }
                    }

                }
            }
            cout<<"��matches��literal������"<<endl;
            vector<string> now_literal = match.getLiteral();
            for(int j = 0; j < now_literal.size(); j++){
                patterns[p].addLiteral(now_literal[j]);
            }
        }
        vector<string> pattern_literal = patterns[p].getLiteral();//��ģʽ�����е�literal
        int literal_size = pattern_literal.size();//m
        if(literal_size > 10){
            int tyy = literal_size/10;
            literal_size = literal_size / tyy;
        }
        if(literal_size > 0){
            int count_gfd = 0;
            for(int i = 0; i < literal_size; i++){
                if(count_gfd >= 100){break;}
                vector<string> copy_literal = pattern_literal;//copyһ��literal����
                string Y = pattern_literal[i];//ѡ��һ��literal��ΪY
                copy_literal.erase(copy_literal.begin() + i);//��copy��ɾ��Y
                for (int n = 1; n < literal_size; n++){//n
                    vector<int> the_array(literal_size - 1, 0);
                    for(int j=0; j < n; j++){
                        the_array[j] = 1;
                    }//��ʼ������the_array
                    //cout<<n<<endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    //cout<<the_array[0]<<the_array[1]<<the_array[2]<<endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    int cnt = 0;
                    int ifend = 0;
                    while(true){
                        vector<string> X;
                        for(int j = 0; j < the_array.size();j++){
                            if(the_array[j] == 1){
                                X.push_back(copy_literal[j]);
                            }
                        }
                        /*
                        cout<<"Y: "<<Y<<endl;
                        cout<<"X: "<<endl;
                        for(int z = 0; z < X.size(); z++){
                            cout<<X[z]<<" ";
                        }
                        cout<<endl;
                        cout<<endl;
                        */
                        //��ʼ��֤
                        int satisfy_XY = 1;
                        int temp_spt = 0;
                        vector<int> privots;
                        for(int it = 0; it < matchs.size(); it ++){//��ƥ��ͼ����
                            Match vad_match = matchs[it];
                            int satisfy_X = 1;
                            int satisfy_Y = 1;
                            int temp_privot = vad_match.getPivot();
                            vector<string> vad_literal = vad_match.getLiteral();

                            for(int j = 0; j < X.size(); j++){
                                if(count(vad_literal.begin(), vad_literal.end(), X[j]) == 0){//������X
                                    satisfy_X = 0;
                                    break;
                                }
                            }
                            if (satisfy_X == 1){
                                if(count(vad_literal.begin(), vad_literal.end(), Y) == 0){//������Y
                                    satisfy_XY = 0;
                                }
                                else {
                                    if(!is_contain(privots, temp_privot)){
                                        temp_spt ++;
                                        privots.push_back(temp_privot);
                                    }
                                }
                            }

                        }//��֤����
                        if(satisfy_XY == 1) {

                            Match temp_match = matchs[0];
                            GFD gfd(temp_match.getSetV(),temp_match.getSetE_value(), temp_match.getSetE_st(),temp_match.getSetE_dst(), Y, X);
                            gfd.setSupport(temp_spt);
                            gfd.setPrivots(privots);

                            int ifadd = 1;
                            for(int temp = 0; temp < GFDs.size(); temp++){
                                if(isSubset(X, GFDs[temp].getX()) == 1 && Y == GFDs[temp].getY() || temp_spt == 0){
                                    ifadd = 0;
                                }
                            }
                            if(ifadd == 1){
                                GFDs.push_back(gfd);
                                packet.push_back(gfd);
                                count_gfd++;
                                if(count_gfd >= 100){break;}
                                cout<<"�ҵ�һ��gfd "<<count_gfd<<endl;
                                gfd.coutGFD();
                            }

                        }
                        cnt = 0;
                        ifend = 1;
                        for(int j=the_array.size() - n; j < the_array.size();j++){
                            if(the_array[j] == 0) {
                                ifend = 0;
                            }
                        }
                        if(ifend == 1){
                            break;
                        }
                        //cout<<"�任ǰ��"<<the_array[0]<<the_array[1]<<the_array[2]<<endl;//����������������������������
                        for(int j=0; j < the_array.size() - 1;j++){
                            if(the_array[j] == 1){
                                if(the_array[j+1] == 0){
                                    the_array[j] = 0;
                                    the_array[j+1] = 1;
                                    for(int k=0;k < j; k++ ){
                                        the_array[k] = 0;
                                    }
                                    for(int k=0; k < cnt; k++){
                                        the_array[k] = 1;
                                    }
                                    break;
                                }
                                else{
                                    cnt++;
                                }
                            }
                        }
                        //cout<<"�任��"<<the_array[0]<<the_array[1]<<the_array[2]<<endl;//������������������������������������
                    }
                    cout<<"�˳�ѭ��"<<endl;
                }
            }
        }
        cout<<"Ū��һ��pattern"<<endl;
        int level = matchs[0].getSetV().size();
        for(int k = 0; k < packet.size(); k++){
            PwithGFDs[pot[level] + p].addGFD(packet[k]);
        }
        cout<<"��ʼһ��pattern"<<endl;
    }
	cout<<"number of GFD found is: "<<GFDs.size()<<endl;
	cout<<endl;
	cout<<"�����˳�"<<endl;
	outFile<<"�����˳�"<<endl;
	/*
	for(int i = 0; i < GFDs.size(); i++){
        GFDs[i].coutGFD();
	}
	*/
    return GFDs;
}
