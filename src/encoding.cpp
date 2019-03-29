
#include "encoding.h"
#include "pqueue.h"

HuffmanNode* buildTreeHelper(PriorityQueue<HuffmanNode*>& pqueue);
void buildMapHelpr(HuffmanNode* node, Map<int, string> &encodingMap, string &path);
void writeToOutput(string encodedChar, obitstream& output);
bool decodeDataHelper(ibitstream& input, HuffmanNode* node, ostream& output);

// STEP : 01
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


// STEP : 02
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {

    PriorityQueue<HuffmanNode*> pqueue;
    for(int key : freqTable){
        int priority = freqTable.get(key);
        HuffmanNode* node = new HuffmanNode(key, priority);
        pqueue.add(node, priority);
    }

    return buildTreeHelper(pqueue);
}

HuffmanNode* buildTreeHelper(PriorityQueue<HuffmanNode*>& pqueue){
    if(pqueue.size() == 1){
        return pqueue.dequeue();
    }else{
        HuffmanNode* zero = pqueue.dequeue();
        HuffmanNode* one = pqueue.dequeue();

        int total = zero->count + one->count;
        HuffmanNode* baseNode = new HuffmanNode();
        baseNode->count = total;
        baseNode->zero = zero;
        baseNode->one = one;

        pqueue.enqueue(baseNode, total);
        return buildTreeHelper(pqueue);
    }
}

// STEP : 03
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    string path = "";
    buildMapHelpr(encodingTree, encodingMap, path);
    return encodingMap;
}

void buildMapHelpr(HuffmanNode* node, Map<int, string> &encodingMap, string &path){
    if(node->isLeaf()){
        encodingMap.put(node->character, path);
    }else{
        path = path + "0";
        buildMapHelpr(node->zero, encodingMap, path);
        path.pop_back();
        path = path + "1";
        buildMapHelpr(node->one, encodingMap, path);
        path.pop_back();
    }
}

// STEP : 04
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    while(true){
        int key = input.get();
        if(key == -1)break;
        string encodedChar = encodingMap.get(key);
        writeToOutput(encodedChar, output);
    }
    string encodedEOF = encodingMap.get(PSEUDO_EOF);
    writeToOutput(encodedEOF, output);
}

void writeToOutput(string encodedChar, obitstream& output){
    for(int i=0; i<encodedChar.size(); i++){
        int bit = (encodedChar[i] == '0')? 0 : 1;
        output.writeBit(bit);
    }
}

// STEP : 05
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    while (true) {
        if(decodeDataHelper(input, encodingTree, output)) break;
    }
}

bool decodeDataHelper(ibitstream& input, HuffmanNode* node, ostream& output){
    if(node->isLeaf()){
        if(node->character == PSEUDO_EOF) return true;
        output.put(node->character);
        return false;
    }else{
        if(input.readBit() == 0){
            return decodeDataHelper(input, node->zero, output);
        }else {
            return decodeDataHelper(input, node->one, output);
        }
    }
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
