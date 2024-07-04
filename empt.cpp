
struct arr{
    int* arr;
    int size;

};
template <class A>
void _swap(A &thing, A &b)
{
    A temp = thing;
    thing = b;
    b = temp;
}


int check(arr &a)
{
    int total = 1;

    for(unsigned int i = 0; i<a.size; i++)
    {
        if(total <= INT_MAX / a.arr[i])
        {
            total*=a.arr[i];
        } 
        else throw(overflow_error);
    }
   
    return total;
}