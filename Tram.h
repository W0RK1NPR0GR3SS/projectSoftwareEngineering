//
//  Tram.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef INC_TRAM_H
#define INC_TRAM_H

#include <string>

class Tram {
private:
  Tram* initCheck;
  int lijnNr;
  int zitplaatsen;
  int passagiers;
  std::string beginStation;
  std::string currentStation;
  int snelheid;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(); // default
  /**
  \n REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  \n REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  \n REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(const int lijnNr, const int zitplaatsen, const std::string& beginStation,
	  const int snelheid); // full

  // DESTRUCTOR
  ~Tram();

  // INITIALIZATION CHECK
  bool properlyInitialized() const;

  // GETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getLijnNr");
  */
  int getLijnNr() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
  */
  int getZitplaatsen() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
  */
  std::string getBeginStation() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  */
  std::string getCurrentStation() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
  */
  int getSnelheid() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getPassagiers");
  */
  int getPassagiers() const;

  // SETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
  \n REQUIRE(newLijnNr >= 0 , "newLijnNr must be bigger or equal to zero");
  \n ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
  */
  void setLijnNr(const int newLijnNr);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
  \n REQUIRE(newZitplaatsen >= 0 , "newZitplaatsen must be bigger or equal to zero");
  \n ENSURE(getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
  */
  void setZitplaatsen(const int newZitplaatsen);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
  \n ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
  */
  void setBeginStation(const std::string& newBeginStation);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  \n ENSURE(getCurrentStation() == newCurrentStation, "setCurrentStation post condition failure");
  */
  void setCurrentStation(const std::string& newCurrentStation);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
  \n REQUIRE(newSnelheid >= 0 , "newSnelheid must be bigger or equal to zero");
  \n ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
  */
  void setSnelheid(const int newSnelheid);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setPassagiers");
  \n REQUIRE(newPassagiers >= 0 , "newPassagiers must be bigger or equal to zero");
  \n ENSURE(getPassagiers() == newPassagiers, "setPassagiers post condition failure");
  */
  void setPassagiers(const int newPassagiers);

  // // MODIFIER METHODS
  // /**
  // \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getOff");
  // \n REQUIRE(off <= getPassagiers(), "More passengers getting off Tram than on Tram");
  // \n ENSURE(getPassagiers() <= getZitplaatsen(), "getOff post condition failure");
  // */
  // void getOff(int off);
  // /**
  // \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getOn");
  // \n REQUIRE(on <= getZitplaatsen() - getPassagiers(), "Not enough seats for passengers getting on Tram");
  // \n ENSURE(getPassagiers() <= getZitplaatsen(), "getOn post condition failure");
  // */
  // void getOn(int on);

protected:

};


#endif /* INC_TRAM_H */
