#ifndef IMAGEPIXEL_LABEL_H
#define IMAGEPIXEL_LABEL_H


class Label {
    int labelID;
    int score;

public:
    Label() : labelID(0), score(0) {}
    explicit Label(int label) : labelID(label), score(0) {}
    Label(int label, int score) : labelID(label), score(score) {}
    ~Label() = default;
    Label(const Label& label){
        this->labelID = label.labelID;
        this->score = label.score;
    }

    void set_id(int label){
        labelID = label;
    }
    int get_id(){
        return labelID;
    }
    void set_score(int score){
        this->score = score;
    }
    int get_score(){
        return score;
    }
};


#endif //IMAGEPIXEL_LABEL_H
