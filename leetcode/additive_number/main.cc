class Solution {
public:
    bool isAdditiveNumber(string num) {
       for (int i = 1; i <= num.size()/2; i++) {
           for (int j = 1; j <= (num.size() - i)/2; j++) {
               string num1 = num.substr(0, i);
               string num2 = num.substr(i, j);
               string num3 = num.substr(i+j);
               if (valid(num1, num2, num3)) return true;
           }
       }
        return false;
    }
    
    bool valid(string num1, string num2, string num3) {
        if(num1.size()>1 && num1[0]=='0' || num2.size()>1 && num2[0]=='0' || num3.size()>1 && num3[0] == '0') return false;
        string sum = add(num1, num2);
        if (sum == num3) {
            return true;
        } else if (sum.size() >= num3.size() || sum.compare(num3.substr(0, sum.size())) != 0){
            return false;
        } else {
            return valid(num2, sum, num3.substr(sum.size()));
        }
    }
    
    string add(string num1, string num2) {
        int i = num1.size()-1, j = num2.size()-1;
        int carry = 0;
        string result;
        while(i >=0 || j >= 0) {
            int sum = carry + (i >= 0 ? num1[i--]-'0' : 0) + (j >=0 ? num2[j--]-'0' : 0);
            carry = sum/10;
            result.push_back(sum%10+'0');
        }
        
        if (carry != 0) result.push_back(carry+'0');
        reverse(result.begin(), result.end());
        return result;
    }
};
