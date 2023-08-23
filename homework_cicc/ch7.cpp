#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <time>

using namespace std;

struct TradeItem {
    TradeItem(const char *date, const char *open, const char *high, const char *low, const char *close) :
            date(date),
            open(strtod(open, nullptr)),
            high(strtod(high, nullptr)),
            low(strtod(low, nullptr)),
            close(strtod(close, nullptr)) {
    }
    double open;
    double high;
    double low;
    double close;
    string date;
};

vector<double> fluctuation;
vector<double> upDateCount;
vector<double> downDateCount;

vector<TradeItem> tradeData;
unordered_map<string, int> dataIndex;

vector<string> split(const string& str, char delim) {
    vector<string> elems;
    auto lastPos = str.find_first_not_of(delim, 0);
    auto pos = str.find_first_of(delim, lastPos);
    while (pos != string::npos || lastPos != string::npos) {
        elems.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delim, pos);
        pos = str.find_first_of(delim, lastPos);
    }
    return elems;
}

void readFile() {
    ifstream inFile;
    string baseDir = std::filesystem::current_path();

    inFile.open(baseDir + "/BTC-Daily.csv", ios_base::in);
    if (!inFile.is_open())
    {
        cout << "Read Error" << endl;
        return;
    }

    string line;
    getline(inFile, line);

    int i = 0;
    while (getline(inFile, line)) {
        line = line.substr(0, line.size() - 1);
        vector<string> infos;
        infos = split(line, ',');
        string date = infos[1].substr(0, 10);
        tradeData.push_back(
            *new TradeItem(date.c_str(), infos[3].c_str(), infos[4].c_str(), infos[5].c_str(), infos[6].c_str()));
        ++i;
    }
    reverse(tradeData.begin(), tradeData.end());
    inFile.close();
}

void preProcess() {
    // calculate daliy change
    for (int i = 0; i < tradeData.size(); ++i) {
        fluctuation[i] = tradeData[i].close - tradeData[i].open;
    }

    // pre process 
    dataIndex[tradeData[0].date] = 0;
    if (fluctuation[0] > 0) {
        upDateCount[0] = 1;
        downDateCount[0] = 0;
    } else {
        upDateCount[0] = 0;
        downDateCount[0] = 1;
    }

    for (auto j = 1; j < tradeData.size(); j++) {
        dataIndex[tradeData[j].date] = j;
        if (fluctuation[j] > 0) {
            upDateCount[j] = upDateCount[j - 1] + 1;
            downDateCount[j] = 0;
        } else {
            upDateCount[j] = 0;
            downDateCount[j] = downDateCount[j - 1] + 1;
        }
    }
}


void greaterThanDateCount(const string &sDate, const string &eDate, double price) {
    int cnt = 0;
    for (auto i = dataIndex[sDate]; i <= dataIndex[eDate]; i++) {
        if (tradeData[i].close > price)
            ++cnt;
    }
    cout << "给定日期区间内价格高于" << price << "的天数: " << cnt << endl;
}

void getMaxPriceDate(const string &sDate, const string &eDate) {
    double max = 0;
    vector<string> dates;
    for (auto i = dataIndex[sDate]; i <= dataIndex[eDate]; i++) {
        if (tradeData[i].close > max) {
            dates.clear();
            max = tradeData[i].close;
            dates.push_back(tradeData[i].date);
        } else {
            if (tradeData[i].close == max) {
                dates.push_back(tradeData[i].date);
            }
        }
    }

    cout << "给定日期区间内价格最高的日期: ";
    for (const auto &date : dates) {
        cout << date << " ";
    }
    cout << endl;
}

void upRange(int dateCount) {
    cout << "连续上涨超过" << dateCount << "天的日期区间为 " << endl;
    for (auto i = 0; i < upDateCount.size(); i++) {
        if (upDateCount[i] > dateCount && (i == end || upDateCount[i] == 0)) {
            cout << "\t(" << tradeData[i - upDateCount[i] + 1].date << " -- " << tradeData[i].date << ")" << endl;
        }
    }

}

void downRange(int dateCount) {
    cout << "连续下跌超过" << dateCount << "天的日期区间为 " << endl;
    for (auto i = 0; i < downDateCount.size(); i++) {
        if (downDateCount[i] > dateCount && (i == end || downDateCount[i] == 0)) {
            cout << "\t(" << tradeData[i - downDateCount[i] + 1].date << " -- " << tradeData[i].date << ")" << endl;
        }
    }
}

void greaterUpDateInRange(const string &sDate, const string &eDate, float given_float) {

    cout << "单日涨幅超过" << given_float << "的日期为" << endl;
    for (auto i = dataIndex[sDate]; i <= dataIndex[eDate]; i++) {
        if (fluctuation[i] > given_float) {
            cout << tradeData[i].date << " ";
        }
    }
    cout << endl;
}

float maxProfit(double buy, const string &sDate, const string &eDate) {
    double buyIn = tradeData[dataIndex[sDate]].low;
    double saleOut = tradeData[dataIndex[eDate]].high;
    double profit = buy / buyIn * saleOut - buy;

    cout << "收益: " << profit << endl;

    return 0;
}