/*

bit 相关的操作 bit_operations 比特操作
思考一下（在进行bit操作的时候）int和uint的区别（补码和原码在表示正数的时候是一样的）
[todo] 还有很多种类的操作要补充
推荐例题：AtCoder/Regular_Contest_182/b.cpp

*/

namespace bit {

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

// todo 查询某一位是 0 or 1

} // namespace bit