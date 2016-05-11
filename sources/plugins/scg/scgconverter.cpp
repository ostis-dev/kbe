#include "scgconverter.h"
#include <QTextStream>
#include <QFile>
#include <QApplication>
#include <QClipboard>
#include <QRadioButton>
struct node{
    int type;
    QString idtf;
    QString id;
    QString parentId;
};

QVector<node> elementNode;

struct arc{
    int type;
    QString bId;
    QString eId;
    QString id;
    QString parentId;
};

QVector<arc> elementArc;

struct pair{
    int type;
    QString bId;
    QString eId;
    QString id;
    QString parentId;
};

QVector<pair> elementPair;

struct contour{
    QString name;
    QString id;
    QString parendId;
};

QVector<contour> elementContour;

struct bus{
    QString owner;
    QString id;
};

QVector<bus> elementBus;


QString fileText;

SCgConverter::SCgConverter(QByteArray array){
 fileText = QString::fromUtf8(array.data());

}

void SCgConverter::startConverter() {
   elementArc.clear();
   elementNode.clear();
   elementPair.clear();
   elementContour.clear();
   elementBus.clear();

    QTextStream cout(stdout);
    int dif;
    cout<<fileText<<endl<<endl;
    for (int index=0; index<fileText.length()-10;index++){
        if (findString(index,"<node")){
            node newNode;
            dif = index;
            while (!findString(dif,"</node>")){ // пока нет конца описания узла

                //поиск id
                if (findString(dif,"id=")){
                    QString str=returnString(dif,"id=");
                    newNode.id=str;
                }

                //поиск idtf
                if (findString(dif,"idtf=\"")){
                    QString str=returnString(dif,"idtf=");
                    newNode.idtf=str;
                  //  cout<<str;
                }

                if (findString(dif,"parent=\"")){
                    QString str=returnString(dif,"parent=");
                    newNode.parentId=str;
                  //  cout<<str;
                }

                //поиск типа
                if (findString(dif,"node/const/group"))
                    newNode.type=(1);
                if (findString(dif,"node/const/relation"))
                   newNode.type=(2);
                if (findString(dif,"node/const/attribute"))
                    newNode.type=(3);
                if (findString(dif,"node/const/asymmetry"))
                    newNode.type=(4);
                if (findString(dif,"node/const/general_node"))
                    newNode.type=(5);

                dif++;
                }
            elementNode.append(newNode);
        }



        if (findString(index,"<arc")){
            dif = index;

             arc newArc;
            while (!findString(dif,"</arc>")){
                //поиск begin id

                if (findString(dif,"id=")){
                    QString str=returnString(dif,"id=");
                    newArc.id=str;

                }

                if (findString(dif,"parent=\"")){
                    QString str=returnString(dif,"parent=");
                    newArc.parentId=str;
                  //  cout<<str;
                }

                if (findString(dif,"id_b=")){
                    QString str=returnString(dif,"id_b=");
                    newArc.bId=str;
                }

                if (findString(dif,"id_e=")){
                    QString str=returnString(dif,"id_e=");
                    newArc.eId=str;
                }

                if (findString(dif,"arc/const/pos"))
                    newArc.type=1;

                dif++;

            }
            elementArc.append(newArc);

        }
        if (findString(index,"<pair")){
            dif = index;

             pair newPair;
            while (!findString(dif,"</pair>")){
                //поиск begin id

                if (findString(dif,"id=")){
                    QString str=returnString(dif,"id=");
                    newPair.id=str;

                }

                if (findString(dif,"id_b=")){
                    QString str=returnString(dif,"id_b=");
                    newPair.bId=str;
                }

                if (findString(dif,"id_e=")){
                    QString str=returnString(dif,"id_e=");
                    newPair.eId=str;
                }

                if (findString(dif,"parent=\"")){
                    QString str=returnString(dif,"parent=");
                    newPair.parentId=str;
                  //  cout<<str;
                }

                if (findString(dif,"pair/const/orient"))
                    newPair.type=1;
                if (findString(dif,"pair/const/synonym"))
                    newPair.type=2;

                dif++;

            }
            elementPair.append(newPair);

        }


        if (findString(index,"<contour")){
            dif = index;

            contour newContour;
            while (!findString(dif,"</contour>")){

                if (findString(dif,"id=")){
                    QString str=returnString(dif,"id=");
                    newContour.id=str;

                }

                if (findString(dif,"parent=\"")){
                    QString str=returnString(dif,"parent=");
                    newContour.parentId=str;
                  //  cout<<str;
                }

                dif++;
            }
            newContour.name="Contour"+QString::number(elementContour.length()+1);
            elementContour.append(newContour);

        }

        if (findString(index,"<bus")){
            dif = index;

             bus newBus;
            while (!findString(dif,"</bus>")){
                //поиск begin id

                if (findString(dif,"id=")){
                    QString str=returnString(dif,"id=");
                    newBus.id=str;

                }

                if (findString(dif,"owner=")){
                    QString str=returnString(dif,"owner=");
                    newBus.owner=str;
                }
                dif++;
            }
            elementBus.append(newBus);
        }
      }

    for (int index=0;index<elementContour.length();index++){
        node newNode;
        newNode.id=elementContour[index].id;
        newNode.idtf=elementContour[index].name;
        newNode.parentId=elementContour[index].parentId;
        newNode.type=5;
        cout<<newNode.parentId<<" "<<newNode.id<<"\n";
        elementNode.append(newNode);
    }


    createSCS();
}

void SCgConverter::createSCS(){
     QTextStream cout(stdout);

    QFile file("out.txt");
    file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadOnly | QIODevice::Truncate);
    QTextStream out(&file);
    out.setCodec("UTF8");

  //  for (int index = 0; index < elementNode.length(); index++) cout<<nodeType[index];

    for (int index = 0; index < elementNode.length(); index++)
        if (elementNode[index].type==1)
            out<<"sc_node_not_relation -> "<<elementNode[index].idtf<<";;\n";

    for (int index = 0; index < elementNode.length(); index++)
        if (elementNode[index].type==2)
            out<<"sc_node_norole_relation -> "<<elementNode[index].idtf<<";;\n";

    for (int index = 0; index < elementNode.length(); index++)
        if (elementNode[index].type==3)
            out<<"sc_node_role_relation -> "<<elementNode[index].idtf<<";;\n";


    file.close();

    for (int index=0;index<elementBus.length();index++) {
        for (int indexArc = 0; indexArc<elementArc.length();indexArc++)
            if (elementArc[indexArc].bId==elementBus[index].id) elementArc[indexArc].bId=elementBus[index].owner;
        for (int indexPair = 0; indexPair<elementPair.length();indexPair++)
            if (elementPair[indexPair].bId==elementBus[index].id) elementPair[indexPair].bId=elementBus[index].owner;
    }


  //  QTextStream out(&file);
   // out.setCodec("UTF8");

    for (int index=0;index<elementContour.length();index++){
        file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadOnly);
        QTextStream out(&file);
        out.setCodec("UTF8");
        out<<elementContour[index].name<<" =  \n [* ";

       /* node newNode;
        newNode.id=elementContour[index].id;
        newNode.idtf=elementContour[index].name;
        newNode.parentId="0";
        newNode.type=5;
        elementNode.append(newNode);*/
        file.close();
        createBunchRelation(elementContour[index].id);
        createBinaryRelation(elementContour[index].id);
        createApplianceRelation(elementContour[index].id);
        file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadOnly);

        out<<" *];; \n";
        file.close();
    }
    file.close();

    createBunchRelation("0");
    createBinaryRelation("0");
    createApplianceRelation("0");

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QApplication::clipboard()->setText(QString(file.readAll()));
        cout<<QString(file.readAll());
        file.close();

}

void SCgConverter::createBunchRelation(QString parent){


    QFile file("out.txt");
    file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadOnly);
    QTextStream out(&file);
    out.setCodec("UTF8");


    // поиск конструкций со связкой и бинарным отношением
for (int index=0;index<elementNode.length();index++)
    if (elementNode[index].type==4 && elementNode[index].parentId==parent){
        for (int indexPair=0; indexPair<elementPair.length();indexPair++)
            if (elementPair[indexPair].bId==elementNode[index].id){

                for (int indexMainNode=0; indexMainNode<elementNode.length();indexMainNode++)
                    if (elementNode[indexMainNode].id==elementPair[indexPair].eId){
                        out<<elementNode[indexMainNode].idtf<<" <= ";

                    }

                for (int indexRelationArc=0; indexRelationArc<elementArc.length();indexRelationArc++)
                    if (elementArc[indexRelationArc].eId==elementPair[indexPair].id)
                       for (int indexRelationNode=0; indexRelationNode< elementNode.length();indexRelationNode++)
                           if (elementNode[indexRelationNode].id==elementArc[indexRelationArc].bId)
                               out<<elementNode[indexRelationNode].idtf<<": ... \n"<<"(* \n";



            }
          for (int indexArc =0; indexArc<elementArc.length();indexArc++){
              bool qq=false;
              if (elementArc[indexArc].bId==elementNode[index].id){
                  for (int indexRelationArc=0; indexRelationArc<elementArc.length();indexRelationArc++)
                      if (elementArc[indexRelationArc].eId==elementArc[indexArc].id)
                          for (int indexRelationNode=0; indexRelationNode< elementNode.length();indexRelationNode++)
                              if (elementNode[indexRelationNode].id==elementArc[indexRelationArc].bId){
                                  out<<" -> "<<elementNode[indexRelationNode].idtf<<": ";
                                  qq=true;
                              }

                  for (int indexNode =0;indexNode<elementNode.length();indexNode++)
                      if (elementNode[indexNode].id==elementArc[indexArc].eId)
                            if (qq) out<<elementNode[indexNode].idtf<<";; \n";
                                else out<<" -> "<<elementNode[indexNode].idtf<<";; \n";
              }
          }
        out<<"*);; \n";
       }
file.close();
}

void SCgConverter::createApplianceRelation(QString parent){


    QFile file("out.txt");
    file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadOnly);
    QTextStream out(&file);
    out.setCodec("UTF8");

    //строим отношение пренадлежности
for (int index=0;index<elementArc.length();index++)
    if (elementArc[index].parentId==parent)
{
    QString begin;
    QString end;
    QString bIdtf;
    QString eIdtf;
    begin=elementArc[index].bId;
    end=elementArc[index].eId;
    for (int newIndex = 0; newIndex<elementNode.length();newIndex++){
        if(elementNode[newIndex].id==begin) bIdtf=elementNode[newIndex].idtf;
        if(elementNode[newIndex].id==end) eIdtf=elementNode[newIndex].idtf;
    }
    QString ans;

     if (bIdtf!=0 && eIdtf!=0){
         out<<bIdtf<<" -> ";
    for (int indexSecondArc=0; indexSecondArc<elementArc.length(); indexSecondArc++){
        if (elementArc[indexSecondArc].eId==elementArc[index].id){
            for (int l=0;l<elementNode.length();l++)
                if (elementArc[indexSecondArc].bId==elementNode[l].id) ans=elementNode[l].idtf;
            out<<ans<<": ";
            //<<eIdtf<<";;\n";
        }
    }

    out<<eIdtf<<";;\n";
    }
}
file.close();
}

void SCgConverter::createBinaryRelation(QString parent){


    QFile file("out.txt");
    file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadOnly);
    QTextStream out(&file);
    out.setCodec("UTF8");

    // бинарное отношение
    for (int index=0;index<elementPair.length();index++)
        if (elementPair[index].parentId==parent)
    {
        QString begin;
        QString end;
        QString bIdtf;
        QString eIdtf;
        begin=elementPair[index].bId;
        end=elementPair[index].eId;
        QString idPair = elementPair[index].id;
        for (int newIndex = 0; newIndex<elementNode.length();newIndex++){
            if(elementNode[newIndex].id==begin && elementNode[newIndex].type!=4) bIdtf=elementNode[newIndex].idtf;
            if(elementNode[newIndex].id==end && elementNode[newIndex].type!=4) eIdtf=elementNode[newIndex].idtf;
        }

        QString ans;
        for (int k=0;k<elementArc.length();k++){
            if (elementArc[k].eId==idPair){
                for (int l=0;l<elementNode.length();l++)
                    if (elementArc[k].bId==elementNode[l].id && elementNode[l].type!=4) ans=elementNode[l].idtf;
                if (elementPair[index].type==1 && bIdtf!="" && eIdtf!="")
                    out<<bIdtf<<" => "<<ans<<" : "<<eIdtf<<";;\n";
                if (elementPair[index].type==2)
                    out<<bIdtf<<" <=> "<<ans<<" : "<<eIdtf<<";;\n";
            }

        }


    }

file.close();
}

QString SCgConverter::returnString(int thisIndex, QString str){
    thisIndex+=str.length()+1;
    QString newstr="";
    while (fileText[thisIndex]!=QChar('"')){
        newstr += fileText[thisIndex];
        thisIndex++;
    }
    return newstr;
}


bool SCgConverter::findString(int thisIndex, QString str){
    bool idtf= true;
    for (int num = 0; num< str.length(); num++)
        if (fileText[num+thisIndex] != str[num]){
            idtf = false;
            break;
        }

    return idtf;
}

