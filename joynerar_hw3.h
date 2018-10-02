using IntStrMap = std::unordered_map<int, std::string>;
using IntIntMap = std::unordered_map<int, int>;
namespace pid
{
    class pidTree
    {
    public:
        void makeMaps(const std::string& procFlie, IntIntMap& pidPPID, IntStrMap& pidCMD);
        void printTree(const int& pid, IntIntMap& pidPPID, IntStrMap& pidCMD);
    };

}
