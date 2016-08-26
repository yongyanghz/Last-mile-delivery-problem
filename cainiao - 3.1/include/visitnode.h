#ifndef VISITNODE_H
#define VISITNODE_H


class visitnode
{
    public:
        visitnode();
        visitnode(bool is,int load,int loc,int e,int o):
            O2O_(is),amount_(load),locIndex_(loc),eIndex_(e),oIndex_(o){
            }
        virtual ~visitnode();

        bool isO2O(){
            return O2O_;
        }
        int amount(){
            return amount_;
        }
        int locIndex(){
            return locIndex_;
        }
        int eIndex(){ //index in all e-orders
            return eIndex_;
        }
        int oIndex(){//index in all o2o orders
            return oIndex_;
        }

    protected:

    private:
        bool O2O_;
        int amount_;
        int locIndex_;
        int eIndex_; //index in all e-orders
        int oIndex_; //index in all o2o orders
};

#endif // VISITNODE_H
