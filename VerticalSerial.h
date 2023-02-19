#include "public_class_v3.h"
#include <iterator>

#define ADDTO(i, j, match, setV) {                       \
    match.addV(G_V[(setV[i].getNeighbour_V_to()[j])]);                  \
    cout << "i and j:" << i << " " << j << endl;	\
    match.addE(setV[i].getNeighbour_E_to()[j]);                      \
}

#define ADDFROM(i, j, match, setV) {                     \
    match.addV(G_V[(setV[i].getNeighbour_V_from()[j])]);                \
    match.addE(setV[i].getNeighbour_E_from()[j]);                   \
}

#define MAKEMATCH1(setV, match, p, v) {                                  \
    match.addV(v);                                                     \
    if(p == 1) ADDTO(i, j, match, setV);                          \
    if(p != 1) ADDFROM(i, j, match, setV);                                 \
}

#define MAKEMATCHn(setV, match, p, tocopy) {  	\
    match.setMatch(tocopy); \
    if(p == 1) ADDTO(i, j, match, setV);                           \
    if(p != 1) ADDFROM(i, j, match, setV);                                        \
}

#define NEWPATTERN(vcnt, ecnt, patterns, match, pivotId, FaId) {      \
    Pattern pattern(vcnt, ecnt);                  \
    pattern.addMatch(match, pivotId);                  \
    pattern.setPivotId(pivotId);              \
    patterns.push_back(pattern);                \
    PaWithGFD pp(pattern, FaId, PwithGFDs.size());                         \
    PwithGFDs.push_back(pp);                         \
}


class VerticalSerial
{
private:
    vector<Match> lastMatches;
    vector<Match> nowMatches;
    vector<Pattern> patterns;
    vector<Pattern> lastPatterns;
public:
	VerticalSerial(){
	}

void addNowMatches(Match match) {
    nowMatches.push_back(match);
}

void setLastMatches(vector<Match> matches) {
    lastMatches = matches;
    nowMatches.clear();
}

void setLastPatterns(vector<Pattern> ps) {
    lastPatterns = ps;
    patterns.clear();
}

vector<Match> getLastMatches(){
    return lastMatches;
}

vector<Pattern> getLastPatterns(){
    return lastPatterns;
}

vector<Match> getNowMatches(){
    return nowMatches;
}


void vertical_serial(int n) {
    if (n == 1)//涓�涓偣鐨勬儏鍐?
    {
    	cout << "now n = 1" <<endl;
        for (int  i = 0; i < G_V.size(); i++)//鐐圭殑涓暟
        {
            for (int j = 0; j < G_V[i].getNeighbour_V_to().size(); j++)//姣忎釜鐐圭殑閭荤偣
            {
            	cout << "now i = " << i << endl;
                Match tempMatch(2, 1);
                if(G_V[i].getId() == G_V[i].getNeighbour_V_to()[j]){
                	cout << "circle!" << endl;
                	continue;
				}
				//防止自环

                int tempPivotId;
                MAKEMATCH1(G_V, tempMatch, 1, G_V[i]);
                cout << "V size:" << tempMatch.getSetV().size() << endl;
                cout << "Pattern是否为空:  " << patterns.empty() << endl;
                if (patterns.empty())//鑻ユ鏃舵棤pattern
                {
                    tempMatch.setPivot(G_V[i].getId());
                    tempMatch.setSubPaId(PwithGFDs.size());
                    addNowMatches(tempMatch);
                    NEWPATTERN(2, 1, patterns, tempMatch, G_V[i].getId(), -1);
					cout << "第" << patterns.size() << "个pattern" << endl;
					cout << endl;
                }else {
                	int flag = 0;
                    for (int u = 0; u < patterns.size(); u++)
                    {
                        if (checkMatch(patterns[u], tempMatch))//妫�鏌atch鏄惁绗﹀悎pattern
                        {
                            tempMatch.setPivot(G_V[i].getId());
                            tempMatch.setSubPaId(u);
                            addNowMatches(tempMatch);
                            patterns[u].addMatch(tempMatch, G_V[i].getId());
                            cout << "第" << u+1 << "个pattern的第" << patterns[u].getSetMatch().size() << "个match" << endl;
                            cout << endl;
                            flag++;
                            break;
                        }
                    }
                    if(!flag){
                    	tempMatch.setPivot(G_V[i].getId());
                    	tempMatch.setSubPaId(PwithGFDs.size());
                        addNowMatches(tempMatch);
                        NEWPATTERN(2, 1, patterns, tempMatch, G_V[i].getId(), -1);
                        cout << "第" << patterns.size() << "个pattern" << endl;
                        cout << endl;
					}
                }
            }

/*            for (int j = 0; j < G_V[i].getNeighbour_V_from().size(); j++)
            {
                Match tempMatch(2, 1);
                if(G_V[i].getId() == G_V[i].getNeighbour_V_from()[j])//防止自环
                	continue;
                MAKEMATCH1(G_V, tempMatch, 0, G_V[i]);
                cout << "from size:" << tempMatch.getSetV().size() << endl;
                cout << endl;
                if (patterns.empty())
                {
                	cout << "now patterns is empty" <<endl;
                    tempMatch.setPivot(G_V[i].getNeighbour_V_from()[j]);
                    addNowMatches(tempMatch);
                    NEWPATTERN(2, 1, patterns, tempMatch, G_V[i].getNeighbour_V_from()[j]);
                }else {
                    for (int u = 0; u < patterns.size(); u++)
                    {
                        if (!checkMatch(patterns[u], tempMatch))
                        {
                            tempMatch.setPivot(G_V[i].getNeighbour_V_from()[j]);
                            addNowMatches(tempMatch);
                            NEWPATTERN(2, 1, patterns, tempMatch, G_V[i].getNeighbour_V_from()[j]);
                        }else{
                            tempMatch.setPivot(G_V[i].getNeighbour_V_from()[j]);
                            addNowMatches(tempMatch);
                            patterns[u].addMatch(tempMatch, G_V[i].getNeighbour_V_from()[j]);
                        }

                    }
                }
            }     */

        }
    }else{
    cout << "now n = " << n << endl;
    for(int x = 0; x < lastMatches.size(); x++)//鎴愮幆闂skip
    {
    	cout << "now x = " << x <<endl;
        int k[10] = {0};
        for (int i = 0; i < n; i++)
            k[i] = lastMatches[x].getSetV()[i].getId();//閬垮厤鍙栧埌match鍐呭凡鏈夌殑鐐?

        for (int i = 0; i < n; i++)
        {
        	cout << "now i = " << i << endl;
            for (int j = 0; j < lastMatches[x].getSetV()[i].getNeighbour_V_to().size(); j++)//姣忎釜鐐圭殑閭荤偣
            {
            	int fflag = 0;
                for (int o = 0; o < n; o++)
            		if (lastMatches[x].getSetV()[i].getNeighbour_V_to()[j] == k[o])
					{
							fflag++;
							break;
					}
				if(fflag) continue;

				Match tempMatch(n+1, n);
                MAKEMATCHn(lastMatches[x].getSetV(), tempMatch, 1, lastMatches[x]);
                if(tempMatch.getSetV().empty())
                	continue;
                cout << "V size:" << tempMatch.getSetV().size() << endl;
                cout << "Pattern是否为空:  " << patterns.empty() << endl;
                if (patterns.empty())//鑻ユ鏃舵棤pattern
                {
                    tempMatch.setPivot(lastMatches[x].getSetV()[i].getId());
                    tempMatch.setSubPaId(PwithGFDs.size());
                    addNowMatches(tempMatch);
                    NEWPATTERN(n+1, n, patterns, tempMatch, lastMatches[x].getSetV()[i].getId(), lastMatches[x].getSubPaId());
                	cout << "第" << patterns.size() << "个pattern" << endl;
					cout << endl;
				}else {
					int flag = 0;
                    for (int u = 0; u < patterns.size(); u++)
                    {
                        if (checkMatch(patterns[u], tempMatch))//妫�鏌atch鏄惁绗﹀悎pattern
                        {
                        	int tempivot = getMatchPivot(tempMatch, G_V[patterns[u].getPivotId()[0]].getLable());
                            tempMatch.setPivot(tempivot);
                            tempMatch.setSubPaId(pot[n+1] + u);
                            addNowMatches(tempMatch);
                            patterns[u].addMatch(tempMatch, tempivot);
                            cout << "第" << u+1 << "个pattern的第" << patterns[u].getSetMatch().size() << "个match" << endl;
                            cout << endl;
                            flag++;
                            break;
						}
                    }
                    if(!flag){
                            tempMatch.setPivot(lastMatches[x].getSetV()[i].getId());
                            tempMatch.setSubPaId(PwithGFDs.size());
                            addNowMatches(tempMatch);
                            NEWPATTERN(n+1, n, patterns, tempMatch, lastMatches[x].getSetV()[i].getId(), lastMatches[x].getSubPaId());
                        	cout << "第" << patterns.size() << "个pattern" << endl;
							cout << endl;
					}
                }
            }

 /*           for (int j = 0; j < lastMatches[x].getSetV()[i].getNeighbour_V_from().size(); j++)//姣忎釜鐐圭殑閭荤偣
            {
                Match tempMatch(n+1, n);
                MAKEMATCHn(lastMatches[x].getSetV(), tempMatch, 0, lastMatches[x]);
                if(tempMatch.getSetV().empty())
                	continue;
                cout << "from size:" << tempMatch.getSetV().size() << endl;
                cout << endl;
                if (patterns.empty())//鑻ユ鏃舵棤pattern
                {
                    tempMatch.setPivot(lastMatches[x].getSetV()[i].getId());
                    addNowMatches(tempMatch);
                    NEWPATTERN(n+1, n, patterns, tempMatch, lastMatches[x].getSetV()[i].getId());
                }else {
                    for (int u = 0; u < patterns.size(); u++)
                    {
                        if (!checkMatch(patterns[u], tempMatch))//妫�鏌atch鏄惁绗﹀悎pattern
                        {
                            tempMatch.setPivot(lastMatches[x].getSetV()[i].getId());
                            addNowMatches(tempMatch);
                            NEWPATTERN(n+1, n, patterns, tempMatch, lastMatches[x].getSetV()[i].getId());
                        }else {

                            int tempivot = getMatchPivot(tempMatch, G_V[patterns[u].getPivotId()[0]].getLable());
                            tempMatch.setPivot(tempivot);
                            addNowMatches(tempMatch);
                            patterns[u].addMatch(tempMatch, tempivot);
                        }
                    }
                }
            }*/
        }
    }   }
    pot[n+2] = PwithGFDs.size();
    return;
}

vector<Pattern> getPatterns(){
    return patterns;
}

int oneSupportCulc(Pattern pattern) {
    return pattern.getPivotId().size();
}


bool isCircle() {
    /* code */
    return false;
}

void supportSum() {
    /* code */
    return;
}

bool checkVlableCount(Pattern pattern, Match match){
	int lag = 0;
	int l[match.getSetV().size()] = {0};
	Match tm = pattern.getSetMatch()[0];
	for(int i = 0; i < tm.getSetV().size(); i++){
		lag = 0;
		for(int j = 0; j < match.getSetV().size(); j++){
			if(l[j]==0){
				if((checkVlable(tm.getSetV()[i], match.getSetV()[j])) && \
					(match.getVfrom()[j] == tm.getVfrom()[i]) && \
					(match.getVto()[j] == tm.getVto()[i]))
				{
					l[j]++;
					lag++;
					cout << "pattern范例：" << tm.getSetV()[i].getId() << " " << tm.getVfrom()[i] << " " <<tm.getVto()[i] << endl;
					cout << "match：" << match.getSetV()[j].getId() << " " << match.getVfrom()[j] << " " <<match.getVto()[j] << endl;
					break;
				}
			}
		}
		if(!lag) return false;
	}
	return true;
}

bool checkVlable(V v1,V v2){
	if(v1.getLable() == v2.getLable())
			return true;
	return false;
}

bool checkMatch(Pattern pattern, Match match) {
    int ffflag = 0;
    int p[match.getSetE_value().size()] = {0};
    Match tk = pattern.getSetMatch()[0];
    //todo:在同构判断上仍存在问题
    if(!checkVlableCount(pattern, match)) return false;
    for (int i = 0; i < tk.getSetE_value().size(); i++)
    {
        ffflag = 0;
        for (int j = 0; j < match.getSetE_value().size(); j++)
        {
            if(p[j] == 0) {
                if (checkE(tk.getSetE_value()[i], match.getSetE_value()[j]))
                {
                    p[j]++;
                    ffflag++;
                    break;
                }
            }
        }
        if (!ffflag) return false;
    }
    return true;
}

bool checkE(E e1,E e2) {
    if (e1.getLable() == e2.getLable())
        if(G_V[e1.getSt()].getLable() == G_V[e2.getSt()].getLable())
            if(G_V[e1.getDst()].getLable() == G_V[e2.getDst()].getLable())
                return true;

    return false;
}

int getMatchPivot(Match match, int patternPivotLable){
    for (int i = 0; i < match.getSetV().size(); i++)
    {
        if (match.getSetV()[i].getLable() == patternPivotLable)
        {
            return match.getSetV()[i].getId();
        }
    }
    return 0;
}
};


