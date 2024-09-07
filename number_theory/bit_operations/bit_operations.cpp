// 推荐例题：AtCoder/Regular_Contest_182/b.cpp

inline int set_bit(int data, int index)
{
    data = data | (1<<(index-1));
    return data;
}

inline int clear_bit(int data, int index)
{
    data = set_bit(data, index);
    data = data - (1<<(index-1));
    return data;
}

// todo 查询某一位是0 or 1