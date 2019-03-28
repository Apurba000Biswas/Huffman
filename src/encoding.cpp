
#include "encoding.h"
// TODO: include any other headers you need

Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;

    while(true){
        int key = input.get();
        if(key == -1){
            freqTable.put(256, 1);
            break;
        }
        if(freqTable.containsKey(key)){
            int frequency = freqTable.get(key);
            frequency = frequency + 1;
            freqTable.put(key, frequency);
        }else{
            freqTable.put(key, 1);
        }
    }
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // TODO: implement this function
    return NULL;   // this is just a placeholder so it will compile
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    return encodingMap;             // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
