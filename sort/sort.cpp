#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;



void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void printVec(vector<int> vec){
    for(int i =0; i<vec.size();i++)
        cout<< vec[i] << " ";
    cout<<endl;
}




/**********************  radix sort    *******************************/

int get_maxdigit(vector<int> vec){
    int maxval = vec[0];
    int n = vec.size();
    for(int i = 1; i < n ; i++){
        if(vec[i] > maxval)
            maxval = vec[i];
    }
    int maxdigit = 0;
    while(maxval>0){
        maxdigit++;
        maxval /= 10;
    }
    return maxdigit;
}


void radix_MSD_sort_helper(vector<int> &vec, int radix){
    if(radix > 0)
    {
        vector<vector<int> > bucket;
        for(int i = 0; i<10;i++)
            bucket.push_back(vector<int>());
        int n = vec.size();
        int idx;
        for(int i = 0; i < n; i++){
            idx = (vec[i]/radix)%10;
            bucket[idx].push_back(vec[i]);
        }
        for(int i = 0;i < 10; i++){
            if(bucket[i].size()>0)
                radix_MSD_sort_helper(bucket[i],radix/10);
        }

        int mark = 0;
        for(int i =0 ;i<10;i++){
            for(int j = 0;j<bucket[i].size();j++){
                vec[mark++] = bucket[i][j];
            }
        }
    }


}

void radix_MSD_sort(vector<int> &vec){
    cout<<"this is MSD radix_sort"<<endl;
    int maxdigit = get_maxdigit(vec);
    int radix = pow(10,maxdigit);
    radix_MSD_sort_helper(vec,radix);

}


void radix_LSD_sort(vector<int> &vec){
    cout<<"this is LSD radix_sort"<<endl;

    int maxdigit = get_maxdigit(vec);
    int count[10];
    int n = vec.size();
    int radix = 1;
    int data;
    vector<int> temp_vec(n,0);
    for(int digit = 1; digit <= maxdigit;digit++){

        for(int i =0;i<10;i++)
            count[i] = 0;

        for(int i =0 ;i<n ; i++){
            data  = (vec[i]/radix)%10;
            count[data]++;
        }

        for(int i=1;i<10;i++)
            count[i] += count[i-1];

        for(int i = n-1; i>=0;i--){
            data = (vec[i]/radix)%10;
            temp_vec[count[data]-1] = vec[i];
            count[data]--;
        }

        for(int i = 0 ;i<n;i++)
            vec[i] = temp_vec[i];

        radix *= 10;
    }
}

/**********************  count sort    *******************************/
void count_sort(vector<int> &vec){
    cout<<"this is count_sort"<<endl;
    int n = vec.size();
    int maxval = vec[0];
    vector<int> temp_vec(n,0);

    for(int i =1;i<n;i++){
        if (vec[i]>maxval)
            maxval = vec[i];
    }
    vector<int> countvec(maxval+1,0);

    for(int i = 0;i<n;i++)
        countvec[vec[i]]++;

    for(int i= 1;i<=maxval;i++)
        countvec[i] += countvec[i-1];

    for(int i = n-1;i>=0;i--){
        temp_vec[countvec[vec[i]]-1] = vec[i];
        countvec[vec[i]]--;
    }
    for(int i =0 ;i<n;i++)
        vec[i] = temp_vec[i];

}

/**********************  merge sort    *******************************/
void merge_sort(vector<int> &vec, int start, int end){
    if (start < end)
    {
        int mid = (end - start)/2 + start;
        merge_sort(vec,start,mid);
        merge_sort(vec,mid+1,end);
        vector<int> vecA;
        vector<int> vecB; 
        for(int i =start;i<=mid;i++)
            vecA.push_back(vec[i]);
        for(int j = mid+1;j<=end;j++)
            vecB.push_back(vec[j]);

        int lenA = vecA.size();
        int lenB = vecB.size();

        int i =0,j=0,k=start;
        while(i<lenA && j<lenB){
            if (vecA[i]<= vecB[j])
                vec[k++] = vecA[i++];
            else
                vec[k++] = vecB[j++];
        }
        while(i < lenA){
            vec[k++] = vecA[i++];
        }
        while(j < lenB){
            vec[k++] = vecB[j++];
        }
    }


}

/**********************  shell sort    *******************************/
void shell_sort(vector<int> &vec){
    cout<<"this is shell_sort"<<endl;
    int n = vec.size();
    int gap;
    int target;
    for(gap = n/2; gap >0; gap/=2){
        for(int i =0; i<gap; i++){
            for(int j = i+gap; j<n; j+=gap){
                int k = j;
                target = vec[k];
                while(k-gap>=0 && target < vec[k-gap]){
                    vec[k] = vec[k-gap];
                    k-=gap;
                }
                vec[k] = target;
            }
        }
    }

    return;
}

/**********************  heap sort  O(nlogn)  *******************************/
void max_heapify(vector<int> &vec, int i, int n){
    int curnode = i;
    int child = 2 * i + 1;    
    while(child < n){
        if(child+1<n && vec[child+1] > vec[child])
            child++;
        if(vec[curnode] >= vec[child])
            break;
        swap(vec[curnode], vec[child]);
        curnode = child;
        child = 2*curnode + 1;
    }

    return ;

}
void build_heap(vector<int> &vec){
    int n = vec.size();
    for(int i = n/2 - 1; i >=0 ; i--)
        max_heapify(vec,i,n);
}

void heap_sort(vector<int> &vec){
    cout<<"this is  heap_sort"<<endl;
    int n = vec.size();
    build_heap(vec);
    for(int i = n-1;i>0;i--){
        swap(vec[i],vec[0]);
        max_heapify(vec,0,i);
    }


    return;
}


/********************** straight  selection sort  O(n^2)  *******************************/
void selection_sort(vector<int> &vec){
    cout<<"this is straight selection_sort"<<endl;
    int n = vec.size();
    int min_idx;

    for(int i = 0; i < n-1; i++){
        min_idx = i;
        for(int j=i+1;j<n;j++){
            if(vec[j]<vec[min_idx])
                min_idx = j;
        }
        swap(vec[i],vec[min_idx]); 
    }

    return;
}

/**********************  insertion sort  O(n^2)  *******************************/
void insertion_sort(vector<int> &vec){
    cout<<"this is insertion_sort"<<endl;
    int n = vec.size();
    int j;
    int target;
    for(int i = 1; i < n; i++){
        target = vec[i];
        j = i;
        while( j>0 && target < vec[j-1]){
            vec[j] = vec[j-1];
            j--; 
        }
        vec[j] = target;
    }
    return;

}

/**********************  bubble_sort  O(n^2)  *******************************/
void bubble_sort(vector<int> &vec){
    cout<<"this is bubble_sort"<<endl;
    int n = vec.size();
    int k = n-1;
    while(k>0){
        for(int i= 0; i<k;i++)
            if (vec[i] > vec[i+1])
                swap(vec[i],vec[i+1]);
        k--;
    }
    return;
}

/**********************  quick sort  O(nlogn)  *******************************/
void quick_sort_twopointer(vector<int> &vec, int start, int end){
    if (start >= end)
        return;
    int pivot = vec[start];
    int i = start;
    int j = end;
    while(i<j){
        while( i<j && vec[j] > pivot)
            j--;

        if(i<j)
            vec[i++] = vec[j];

        while(i<j && vec[i] < pivot)
            i++;

        if(i<j)
            vec[j--] = vec[i];
    }

    vec[i] = pivot;
    quick_sort_twopointer(vec, start, i-1);
    quick_sort_twopointer(vec,i+1, end);

    return;
}

// quick sort without recursion
void quick_sort_norecur(vector<int> &vec){
    int n = vec.size();
    vector<int> stack;
    int start,end;
    stack.push_back(0);
    stack.push_back(n-1);

    while(stack.size()>0)
    {
        end = stack.back();
        stack.pop_back();
        start = stack.back();
        stack.pop_back();
        if (start >= end)
            continue;
        else
        {
            int pivot = vec[start];
            int i = start;
            for(int j = start + 1; j <= end; j++)
            {
                if(vec[j] < pivot)
                    swap(vec[++i],vec[j]);
            }
            swap(vec[i],vec[start]);

            stack.push_back(start);
            stack.push_back(i-1);
            stack.push_back(i+1);
            stack.push_back(end);
        }
    }

    return ;
}

void  quick_sort(vector<int> &vec, int start, int end){
    if(start >= end)
        return;

    int pivot = vec[start];
    int i = start;
    for(int j = start + 1; j <= end; j++)
    {
        if(vec[j] < pivot)
            swap(vec[++i],vec[j]);
    }

    swap(vec[i],vec[start]);

    quick_sort(vec, start, i-1);
    quick_sort(vec, i+1, end);

    return;

}

/********************************************************************/


int main(){
    srand (time(NULL));
    vector<int> vec;
    int n = 20;
    for(int i=0;i<n;i++)
        vec.push_back(rand()%100);
    printVec(vec);

    vector<int> vec1(vec); 
    vector<int> vec2(vec); 
    vector<int> vec3(vec); 
    vector<int> vec4(vec); 
    vector<int> vec5(vec); 
    vector<int> vec6(vec); 
    vector<int> vec7(vec); 

    quick_sort(vec1,0,n-1);
    printVec(vec1);
    // quick_sort_twopointer(vec2,0,n-1);
    // printVec(vec2);
    // quick_sort_norecur(vec3);
    // printVec(vec3);
    
    selection_sort(vec2);
    printVec(vec2);

    shell_sort(vec3);
    printVec(vec3);

    cout<<"this is merge_sort"<<endl;
    merge_sort(vec4,0, n-1);
    printVec(vec4);

    count_sort(vec5);
    printVec(vec5);

    radix_LSD_sort(vec6);
    printVec(vec6);

    radix_MSD_sort(vec7);
    printVec(vec7);
}