#include <bits/stdc++.h>
using namespace std;
// use of Segment Tree just Finding Sum .
const int mod = 1e9 + 7;
using ll = long long;

struct SegTree{

    int size ;
    vector<ll> sums;

    void init(int n){
        
        size = 1;
        while(size < n) size *= 2;
        // suppose the n not a power of 4 * n
        // or use 2 * 2^log(n) + 1;
        sums.assign(size * 2,0ll);
    }

    void build(vector<ll>& nums ,int x ,int lx ,int rx){

        if(rx - lx == 1){
            if(lx < (int)nums.size())
                sums[x] = nums[lx];
            return ;    
        }
        int mid = lx + (rx -lx)/2;
        build(nums,2*x+1,lx,mid);
        build(nums,2*x+2,mid,rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void build(vector<ll>& nums){
        build(nums,0,0,size);
    }
    
    void Update(ll val ,int i ,int x ,int lx , int rx){
        
        if(rx - lx == 1){
            sums[x] = val;
            return ;    
        }
        int mid = lx + (rx - lx)/2;
        if(i < mid)
            Update(val,i,2*x+1,lx,mid);
        else
            Update(val,i,2*x+2,mid,rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];

    }

    void Update(int i ,ll val){
        Update(val,i,0,0,size);
    }

    ll sum(int l ,int r ,int x ,int lx ,int rx){

        if(rx <= l || lx >= r)
            return 0;
        if(lx >= l && rx <= r)
            return sums[x];

        int mid = lx + (rx - lx)/2;
        ll sum1 = sum(l,r,2*x+1,lx,mid);
        ll sum2 = sum(l,r,2*x+2,mid,rx);
        return sum1+sum2;

    }

    ll sum(int l ,int r){
        return sum(l,r,0,0,size);
    }

};

void solve(){
    
    int n ,m;
    cin >> n >> m;

    SegTree st;
    st.init(n);
    vector<ll> nums (n);
    for(int i=0;i<n;i++){
        cin >> nums[i];
        }

    st.build(nums);

    while(m--){
        int op;
        cin >> op;
        if(op == 1){
            int i ,v;
            cin >> i >> v;
            st.Update(i,v);
        }else{
            int l ,r;
            cin >> l >> r;
            cout << st.sum(l,r) << endl;
        }
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}