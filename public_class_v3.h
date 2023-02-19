/*
    public_class.h
    公共资源定义�?

	G_V、G_E中按id升序排列
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include<algorithm>
using namespace std;

ofstream outFile("gfds.txt");


class E
{
	private:
		int lable;//边的lable
		int st_id;//边的起始�?
		int dst_id;//边的终点

	public:
	    E(int lab,int st, int dst){
            lable = lab;
            st_id = st;
            dst_id = dst;
	    }

		void setLable(int lab){
			lable = lab;
		}

		int getLable(){
			return lable;
		}

        void setSt(int v) {
            st_id = v;
        }

        void setDst(int v) {
            dst_id = v;
        }

		int getSt() {
			return st_id;
		}

		int getDst() {
			return dst_id;
		}
};

class Match;

class V
{
	private:
		int real_id;//点的唯一标识
		int lable;//点的lable
		//map<string, string> attribute;//点的属性，键为属性的类别，如名字，学�?
		//vector<V> neighbour_V;//该点的邻点集�?
		//vector<E> neighbour_E;//该点的边集合,值为1表示出边�?表示入该点的�?
		vector<string> attribute_key;
		vector<string> attribute_value;
		vector<int> neighbour_V_to;
        vector<int> neighbour_V_from;
		vector<E> neighbour_E_to;
        vector<E> neighbour_E_from;

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
        vector<int> getNeighbour_V_to() {
            return neighbour_V_to;
        }
        vector<int> getNeighbour_V_from() {
            return neighbour_V_from;
        }
        vector<E> getNeighbour_E_to() {
            return neighbour_E_to;
        }
        vector<E> getNeighbour_E_from() {
            return neighbour_E_from;
        }
		int getId(){
            return real_id;
		}
		int getLable(){
            return lable;
		}
        void addNeighbour_to(int v, E e) {
            neighbour_V_to.push_back(v);
            neighbour_E_to.push_back(e);
        }
        void addNeighbour_from(int v, E e) {
            neighbour_V_from.push_back(v);
            neighbour_E_from.push_back(e);
        }
};

class Match//匹配�?
{
	private:
		int pivot_id;
		int v_count;//点的个数
		int e_count;//边的个数
		//unordered_map<int,V> set_v;//点集合，抽象id
		//vector<E> set_e;//边集�?
		//unordered_set<string> match_literal;//该图中的literal集合,垂直时不用添�?
        vector<V> setV;
		vector<E> setE_value;
		vector<int> setE_st;
		vector<int> setE_dst;
		vector<int> vTo;
		vector<int> vFrom;
		vector<string> match_literal;
		int subPaId;

	public:
		Match(int v_count, int e_count){
			v_count = v_count;
			e_count = e_count;
		}

		void setSubPaId(int a){
			subPaId = a;
		}

		int getSubPaId(){
			return subPaId;
		}

		vector<int> getVto(){
			return vTo;
		}

		vector<int> getVfrom(){
			return vFrom;
		}

		void setMatch(Match match){
			setV = match.getSetV();
			setE_value = match.getSetE_value();
			setE_st = match.getSetE_st();
			setE_dst = match.getSetE_dst();
			vTo = match.getVto();
			vFrom = match.getVfrom();
		}

		void addV(V v){
			cout << "addv ID: " << v.getId() << endl;
			setV.push_back(v);
			vFrom.push_back(0);
			vTo.push_back(0);
		}
		void addE(E e){
			setE_value.push_back(e);
			for(int i = 0; i < setV.size(); i ++){
                if(setV[i].getId() == e.getDst()){
                    setE_dst.push_back(i);
                    vFrom[i] = vFrom[i] + 1;
                    cout << setV[i].getId() <<"����ȣ�" << vFrom[i] << endl;
                }
                else if(setV[i].getId() == e.getSt()){
                    setE_st.push_back(i);
                    vTo[i] = vTo[i] + 1;
                    cout << setV[i].getId() <<"����ȣ�" << vTo[i] << endl;
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
		void setPivot(int pivot) {
			pivot_id = pivot;
		}
		int getPivot(){
			return pivot_id;
		}
};

class Pattern
{
	private:
		/*######################
		 *垂直所需要的一些结�?
		 *
		 *######################
		 */
		vector<int> pivot_id;//枢轴点样例的真实id
		int v_count;//点个�?
		int e_count;//边个�?
		//unordered_set<Match> set_match;//该pattern匹配到的图集
		//unordered_set<string> pattern_literal;//所有匹配图的literal并集
		//vector<string> literal_up;//整理过的（换个容器）
		vector<V> setV;
		vector<string> pattern_literal;
		vector<Match> setMatch;
        vector<E> setE;

	public:
		Pattern(){}

		Pattern(int v_coun, int e_coun){
			v_count = v_coun;
			e_count = v_coun;
		}
		void addMatch(Match match, int newPivotId){
			setMatch.push_back(match);
            if (setV.empty())
                setV = match.getSetV();
            if (setE.empty())
                setE = match.getSetE_value();
			vector<int>::iterator it;
			it =find(pivot_id.begin(), pivot_id.end(), newPivotId);
			if(it == pivot_id.end()){
				pivot_id.push_back(newPivotId);
			}
		}
		vector<Match> getSetMatch(){
			return setMatch;
		}
        vector<V> getSetV() {
            return setV;
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
        vector<E> getSetE() {
            return setE;
        }
		void setPivotId(int pivot){
            pivot_id.push_back(pivot);
		}
		vector<int> getPivotId(){
            return pivot_id;
		}
};
static vector<V> G_V;
static vector<E> G_E;

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
                outFile<<"v "<<i<<" "<<setV[i].getLable()<<endl;
            }
            for(int i = 0; i < setE_value.size(); i++){
                outFile<<"e "<<setE_st[i]<<" "<<setE_value[i].getLable()<<" "<<setE_dst[i]<<endl;
            }
            outFile<<"X: "<<X[0];
            for(int i = 1; i < X.size(); i ++){
                outFile<<" && "<<X[i];
            }
            outFile<<endl;
            outFile<<"Y: "<<Y<<endl;
            outFile<<"support: "<<support<<endl;
            outFile<<endl;
		}
};

class PaWithGFD
{
	private:
		int id;
		Pattern nowPattern;
		int FaId;
		vector<GFD> GFDs;

	public:
		PaWithGFD(Pattern paa, int fa, int iid){
			nowPattern = paa;
			FaId = fa;
			id = iid;
		}

		void addGFD(GFD gfd){
			GFDs.push_back(gfd);
		}

		int getFaId(){
			return FaId;
		}

		Pattern getNowPattern(){
			return nowPattern;
		}

		vector<GFD> getGFDs(){
			return GFDs;
		}

		int getId(){
			return id;
		}
};
vector<PaWithGFD> PwithGFDs;			//����vector
int pot[10] = {0};						//pot[i]Ϊi����ĵ�һ��pattern��id��pot[0]pot[1]������
