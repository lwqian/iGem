#include <cstdio>
#include <sbml/SBMLTypes.h>
using namespace std;


void printCompartments(const ListOfCompartments * compartList){
   
   
     cout<<"ListOfCompartments:";
     for(int iter=0;iter<compartList->size();iter++){
         
          const Compartment *compart=compartList->get(iter);
          cout<<"\n\t\tCompartment:"<<compart->getId();
      }

}

void printSpecies(const ListOfSpecies * speciesList){
   
   
     cout<<"\nListOfSpecies:";
     for(int iter=0;iter<speciesList->size();iter++){
         
          const Species *species=speciesList->get(iter);
          cout<<"\n\t\tSpecies: "<<species->getId();
          cout<<"\tCompartment: "<<species->getCompartment();
          cout<<"\tInitialConcentration:"<<species->getInitialConcentration();
          cout<<"\tBoundaryCondition: "<<species->getBoundaryCondition();
      }

}


void printParameters(const ListOfParameters *parameterList){
     
     cout<<"\nListOfParameters:";
     for(int iter=0;iter<parameterList->size();iter++){
      
         const Parameter *parameter=parameterList->get(iter);
         cout<<"\n\t\tParameter: "<<parameter->getId();
         cout<<":"<<parameter->getValue();
      }
}


void printReactionSpecies(const SpeciesReference *species){
 




        if(species->getStoichiometry()>1)
           cout<<species->getStoichiometry();
        cout<<species->getSpecies();

}

void printReactions(const ListOfReactions *reactionList){
 
     cout<<"\nListOfReactions:";
     for(int iter=0;iter<reactionList->size();iter++){
      
         const Reaction *reaction=reactionList->get(iter);
         cout<<"\n\t\tReaction "<<reaction->getId()<<": ";

         const KineticLaw *law=reaction->getKineticLaw();
         const ASTNode *ast=law->getMath(); 
         char  *result = SBML_formulaToString(ast);

         for(int iter=0;iter<reaction->getNumReactants();iter++){

             if(iter>0)
                 cout<<"+";
             //const SpeciesReferences *species=;
            printReactionSpecies(reaction->getReactant(iter));
         }

         if(reaction->getReversible())
           cout<<"<---"<<result<<"--->";
         else
            cout<<"---"<<result<<"--->";
         for(int iter=0;iter<reaction->getNumProducts();iter++){

             if(iter>0)
                 cout<<"+";
          //   const SpeciesReference *species=reaction->getProduct(iter);
             printReactionSpecies(reaction->getProduct(iter));
         }

         
         
      }

}

         
int main()
{
        SBMLReader *reader=new SBMLReader();
	SBMLDocument *sbmlDoc = reader->readSBMLFromFile("oscillator.xml");
        const Model *model=sbmlDoc->getModel();

        const ListOfCompartments *compartList=model->getListOfCompartments();
        printCompartments(compartList);
        
        const ListOfSpecies *speciesList=model->getListOfSpecies();
        printSpecies(speciesList);

        const ListOfParameters *parameterList=model->getListOfParameters();
        printParameters(parameterList);

        const ListOfReactions *reactionList=model->getListOfReactions();
        printReactions(reactionList);
        cout<<"\n";
	return 0;
}
