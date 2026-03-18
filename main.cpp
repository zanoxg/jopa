std::vector<int> fbnc(int number)
{
    std::vector<int> result;
    result.reserve(number + 1);

    result.push_back(0);
    if (number >= 1)
    {
        result.push_back(1);
    }

    for (int i = 2; i <= number; ++i)
    {
        result.push_back(result[i - 1] + result[i - 2]);
    }

    return result
}

int main()
{
    std::vector<int> jopa = fbnc(67);
    for (int number : jopa)
    {
        std::cout << number << std::endl;
    }
    return 0;
}
