#include "reweightingFactors_Old.hh"

namespace Operation {

  std::vector< std::vector<jFitParameters> > init_fit_params_Old() {

    //for the NT7 WJets madgraph sample
    jFitParameters ReweightParams;
    std::vector<std::vector<jFitParameters> > PtYweights(3, std::vector<jFitParameters>(7));
    ReweightParams.alpha_plus = 756.949;
    ReweightParams.alpha_minus = 611.651;
    ReweightParams.beta_plus = 691.321;
    ReweightParams.beta_minus = 662.532;
    ReweightParams.gamma_plus = 288.54;
    ReweightParams.gamma_minus = 251.609;
    PtYweights.at(0).at(0) = ReweightParams;
    ReweightParams.alpha_plus = 928.018;
    ReweightParams.alpha_minus = 632.22;
    ReweightParams.beta_plus = 726.45;
    ReweightParams.beta_minus = 789.993;
    ReweightParams.gamma_plus = 101.79;
    ReweightParams.gamma_minus = 86.4421;
    PtYweights.at(0).at(1) = ReweightParams;
    ReweightParams.alpha_plus = 1036.43;
    ReweightParams.alpha_minus = 559.029;
    ReweightParams.beta_plus = 673.401;
    ReweightParams.beta_minus = 843.381;
    ReweightParams.gamma_plus = 82.5131;
    ReweightParams.gamma_minus = 70.3606;
    PtYweights.at(0).at(2) = ReweightParams;
    ReweightParams.alpha_plus = 1179.43;
    ReweightParams.alpha_minus = 459.249;
    ReweightParams.beta_plus = 589.049;
    ReweightParams.beta_minus = 890.121;
    ReweightParams.gamma_plus = 86.8418;
    ReweightParams.gamma_minus = 59.2452;
    PtYweights.at(0).at(3) = ReweightParams;
    ReweightParams.alpha_plus = 1365.12;
    ReweightParams.alpha_minus = 336.705;
    ReweightParams.beta_plus = 484.263;
    ReweightParams.beta_minus = 916.726;
    ReweightParams.gamma_plus = 86.3948;
    ReweightParams.gamma_minus = 54.3763;
    PtYweights.at(0).at(4) = ReweightParams;
    ReweightParams.alpha_plus = 1543.98;
    ReweightParams.alpha_minus = 206.201;
    ReweightParams.beta_plus = 333.757;
    ReweightParams.beta_minus = 880.763;
    ReweightParams.gamma_plus = 81.571;
    ReweightParams.gamma_minus = 45.7964;
    PtYweights.at(0).at(5) = ReweightParams;
    ReweightParams.alpha_plus = 2954.86;
    ReweightParams.alpha_minus = 125.393;
    ReweightParams.beta_plus = 202.248;
    ReweightParams.beta_minus = 1178.26;
    ReweightParams.gamma_plus = 109.316;
    ReweightParams.gamma_minus = 36.9737;
    PtYweights.at(0).at(6) = ReweightParams;
    ReweightParams.alpha_plus = 37.9662;
    ReweightParams.alpha_minus = 24.3362;
    ReweightParams.beta_plus = 31.7786;
    ReweightParams.beta_minus = 31.01;
    ReweightParams.gamma_plus = 19.2953;
    ReweightParams.gamma_minus = 14.8432;
    PtYweights.at(1).at(0) = ReweightParams;
    ReweightParams.alpha_plus = 39.5252;
    ReweightParams.alpha_minus = 22.2005;
    ReweightParams.beta_plus = 28.9281;
    ReweightParams.beta_minus = 31.6662;
    ReweightParams.gamma_plus = 20.8332;
    ReweightParams.gamma_minus = 14.627;
    PtYweights.at(1).at(1) = ReweightParams;
    ReweightParams.alpha_plus = 46.6887;
    ReweightParams.alpha_minus = 19.223;
    ReweightParams.beta_plus = 26.6167;
    ReweightParams.beta_minus = 32.4838;
    ReweightParams.gamma_plus = 21.0953;
    ReweightParams.gamma_minus = 14.4535;
    PtYweights.at(1).at(2) = ReweightParams;
    ReweightParams.alpha_plus = 52.7514;
    ReweightParams.alpha_minus = 14.9665;
    ReweightParams.beta_plus = 22.6306;
    ReweightParams.beta_minus = 33.6113;
    ReweightParams.gamma_plus = 22.0123;
    ReweightParams.gamma_minus = 12.5927;
    PtYweights.at(1).at(3) = ReweightParams;
    ReweightParams.alpha_plus = 60.0282;
    ReweightParams.alpha_minus = 10.1984;
    ReweightParams.beta_plus = 17.4955;
    ReweightParams.beta_minus = 31.482;
    ReweightParams.gamma_plus = 21.3574;
    ReweightParams.gamma_minus = 10.0748;
    PtYweights.at(1).at(4) = ReweightParams;
    ReweightParams.alpha_plus = 60.8587;
    ReweightParams.alpha_minus = 4.99041;
    ReweightParams.beta_plus = 10.61;
    ReweightParams.beta_minus = 26.0686;
    ReweightParams.gamma_plus = 15.4274;
    ReweightParams.gamma_minus = 6.13445;
    PtYweights.at(1).at(5) = ReweightParams;
    ReweightParams.alpha_plus = 63.187;
    ReweightParams.alpha_minus = 2.06951;
    ReweightParams.beta_plus = 4.60711;
    ReweightParams.beta_minus = 19.6549;
    ReweightParams.gamma_plus = 9.96265;
    ReweightParams.gamma_minus = 2.67331;
    PtYweights.at(1).at(6) = ReweightParams;
    ReweightParams.alpha_plus = 10.4891;
    ReweightParams.alpha_minus = 5.10826;
    ReweightParams.beta_plus = 7.32451;
    ReweightParams.beta_minus = 7.68932;
    ReweightParams.gamma_plus = 1.93854;
    ReweightParams.gamma_minus = 1.64424;
    PtYweights.at(2).at(0) = ReweightParams;
    ReweightParams.alpha_plus = 11.0691;
    ReweightParams.alpha_minus = 4.74347;
    ReweightParams.beta_plus = 7.03086;
    ReweightParams.beta_minus = 7.68455;
    ReweightParams.gamma_plus = 2.70283;
    ReweightParams.gamma_minus = 1.53771;
    PtYweights.at(2).at(1) = ReweightParams;
    ReweightParams.alpha_plus = 12.5091;
    ReweightParams.alpha_minus = 4.04189;
    ReweightParams.beta_plus = 5.98365;
    ReweightParams.beta_minus = 8.0492;
    ReweightParams.gamma_plus = 3.52679;
    ReweightParams.gamma_minus = 1.18959;
    PtYweights.at(2).at(2) = ReweightParams;
    ReweightParams.alpha_plus = 14.1869;
    ReweightParams.alpha_minus = 2.41066;
    ReweightParams.beta_plus = 4.8454;
    ReweightParams.beta_minus = 6.80745;
    ReweightParams.gamma_plus = 3.3326;
    ReweightParams.gamma_minus = 2.19525;
    PtYweights.at(2).at(3) = ReweightParams;
    ReweightParams.alpha_plus = 13.8945;
    ReweightParams.alpha_minus = 1.43339;
    ReweightParams.beta_plus = 3.40143;
    ReweightParams.beta_minus = 5.91432;
    ReweightParams.gamma_plus = 2.14164;
    ReweightParams.gamma_minus = 0.782623;
    PtYweights.at(2).at(4) = ReweightParams;
    ReweightParams.alpha_plus = 10.43;
    ReweightParams.alpha_minus = 0.641139;
    ReweightParams.beta_plus = 1.34938;
    ReweightParams.beta_minus = 3.62771;
    ReweightParams.gamma_plus = 1.31054;
    ReweightParams.gamma_minus = 0.372387;
    PtYweights.at(2).at(5) = ReweightParams;
    ReweightParams.alpha_plus = 5.04662;
    ReweightParams.alpha_minus = 0.122543;
    ReweightParams.beta_plus = 0.320807;
    ReweightParams.beta_minus = 1.27196;
    ReweightParams.gamma_plus = 0.242255;
    ReweightParams.gamma_minus = -0.0795943;
    PtYweights.at(2).at(6) = ReweightParams;
    
    return PtYweights;

  }


  std::vector< std::vector<jFitParameters> > init_fit_params_CSPhi_Old() {

    //this is for use with the NT7 Ntuples (WJets-madgraph)
    jFitParameters CSPhiReweightParams;
    std::vector<std::vector<jFitParameters> > PtYweights(3, std::vector<jFitParameters>(7));
    CSPhiReweightParams.alpha_plus = 183.67;
    CSPhiReweightParams.alpha_minus = 161.346;
    CSPhiReweightParams.beta_plus = 1.04153;
    CSPhiReweightParams.beta_minus = -2.59674;
    CSPhiReweightParams.gamma_plus = 10.3433;
    CSPhiReweightParams.gamma_minus = 4.70622;
    PtYweights.at(0).at(0) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 185.705;
    CSPhiReweightParams.alpha_minus = 159.532;
    CSPhiReweightParams.beta_plus = 0.61337;
    CSPhiReweightParams.beta_minus = -2.52467;
    CSPhiReweightParams.gamma_plus = 5.33592;
    CSPhiReweightParams.gamma_minus = 4.37573;
    PtYweights.at(0).at(1) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 189.502;
    CSPhiReweightParams.alpha_minus = 155.726;
    CSPhiReweightParams.beta_plus = -0.396202;
    CSPhiReweightParams.beta_minus = -2.22786;
    CSPhiReweightParams.gamma_plus = 3.99426;
    CSPhiReweightParams.gamma_minus = 3.8493;
    PtYweights.at(0).at(2) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 196.167;
    CSPhiReweightParams.alpha_minus = 148.932;
    CSPhiReweightParams.beta_plus = 0.954684;
    CSPhiReweightParams.beta_minus = -2.31194;
    CSPhiReweightParams.gamma_plus = 5.08953;
    CSPhiReweightParams.gamma_minus = 4.09319;
    PtYweights.at(0).at(3) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 204.671;
    CSPhiReweightParams.alpha_minus = 138.258;
    CSPhiReweightParams.beta_plus = 2.73241;
    CSPhiReweightParams.beta_minus = -3.43398;
    CSPhiReweightParams.gamma_plus = 6.6607;
    CSPhiReweightParams.gamma_minus = 4.95809;
    PtYweights.at(0).at(4) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 207.17;
    CSPhiReweightParams.alpha_minus = 119.755;
    CSPhiReweightParams.beta_plus = 4.82197;
    CSPhiReweightParams.beta_minus = -4.23649;
    CSPhiReweightParams.gamma_plus = 5.10753;
    CSPhiReweightParams.gamma_minus = 4.11544;
    PtYweights.at(0).at(5) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 345.338;
    CSPhiReweightParams.alpha_minus = 141.738;
    CSPhiReweightParams.beta_plus = 5.50968;
    CSPhiReweightParams.beta_minus = -4.01901;
    CSPhiReweightParams.gamma_plus = 11.8944;
    CSPhiReweightParams.gamma_minus = 0.910881;
    PtYweights.at(0).at(6) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 9.39949;
    CSPhiReweightParams.alpha_minus = 7.4042;
    CSPhiReweightParams.beta_plus = 1.11107;
    CSPhiReweightParams.beta_minus = -1.41559;
    CSPhiReweightParams.gamma_plus = 4.93483;
    CSPhiReweightParams.gamma_minus = 3.8748;
    PtYweights.at(1).at(0) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 9.41211;
    CSPhiReweightParams.alpha_minus = 7.23415;
    CSPhiReweightParams.beta_plus = 1.37689;
    CSPhiReweightParams.beta_minus = -1.52763;
    CSPhiReweightParams.gamma_plus = 4.7049;
    CSPhiReweightParams.gamma_minus = 4.063;
    PtYweights.at(1).at(1) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 9.96498;
    CSPhiReweightParams.alpha_minus = 6.98993;
    CSPhiReweightParams.beta_plus = 2.24921;
    CSPhiReweightParams.beta_minus = -2.04501;
    CSPhiReweightParams.gamma_plus = 5.00492;
    CSPhiReweightParams.gamma_minus = 3.86744;
    PtYweights.at(1).at(2) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 10.2717;
    CSPhiReweightParams.alpha_minus = 6.45495;
    CSPhiReweightParams.beta_plus = 3.59248;
    CSPhiReweightParams.beta_minus = -2.58341;
    CSPhiReweightParams.gamma_plus = 5.07149;
    CSPhiReweightParams.gamma_minus = 3.65214;
    PtYweights.at(1).at(3) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 10.4349;
    CSPhiReweightParams.alpha_minus = 5.46288;
    CSPhiReweightParams.beta_plus = 5.43564;
    CSPhiReweightParams.beta_minus = -2.87941;
    CSPhiReweightParams.gamma_plus = 5.53358;
    CSPhiReweightParams.gamma_minus = 2.54391;
    PtYweights.at(1).at(4) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 9.15874;
    CSPhiReweightParams.alpha_minus = 3.92234;
    CSPhiReweightParams.beta_plus = 6.50807;
    CSPhiReweightParams.beta_minus = -2.90205;
    CSPhiReweightParams.gamma_plus = 4.19074;
    CSPhiReweightParams.gamma_minus = 1.93132;
    PtYweights.at(1).at(5) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 8.19787;
    CSPhiReweightParams.alpha_minus = 2.5722;
    CSPhiReweightParams.beta_plus = 7.91125;
    CSPhiReweightParams.beta_minus = -2.43885;
    CSPhiReweightParams.gamma_plus = 3.92612;
    CSPhiReweightParams.gamma_minus = 1.28377;
    PtYweights.at(1).at(6) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.07417;
    CSPhiReweightParams.alpha_minus = 1.50706;
    CSPhiReweightParams.beta_plus = 0.611531;
    CSPhiReweightParams.beta_minus = -0.559919;
    CSPhiReweightParams.gamma_plus = 1.49317;
    CSPhiReweightParams.gamma_minus = 1.21005;
    PtYweights.at(2).at(0) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.18669;
    CSPhiReweightParams.alpha_minus = 1.46149;
    CSPhiReweightParams.beta_plus = 0.788933;
    CSPhiReweightParams.beta_minus = -0.587234;
    CSPhiReweightParams.gamma_plus = 1.48399;
    CSPhiReweightParams.gamma_minus = 1.01473;
    PtYweights.at(2).at(1) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.31409;
    CSPhiReweightParams.alpha_minus = 1.39517;
    CSPhiReweightParams.beta_plus = 1.18574;
    CSPhiReweightParams.beta_minus = -0.814545;
    CSPhiReweightParams.gamma_plus = 1.69462;
    CSPhiReweightParams.gamma_minus = 1.15418;
    PtYweights.at(2).at(2) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.34842;
    CSPhiReweightParams.alpha_minus = 1.19177;
    CSPhiReweightParams.beta_plus = 1.77321;
    CSPhiReweightParams.beta_minus = -0.869358;
    CSPhiReweightParams.gamma_plus = 1.82971;
    CSPhiReweightParams.gamma_minus = 0.711737;
    PtYweights.at(2).at(3) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.0308;
    CSPhiReweightParams.alpha_minus = 0.852505;
    CSPhiReweightParams.beta_plus = 1.97041;
    CSPhiReweightParams.beta_minus = -0.882047;
    CSPhiReweightParams.gamma_plus = 1.72467;
    CSPhiReweightParams.gamma_minus = 0.657063;
    PtYweights.at(2).at(4) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 1.35938;
    CSPhiReweightParams.alpha_minus = 0.474755;
    CSPhiReweightParams.beta_plus = 1.72746;
    CSPhiReweightParams.beta_minus = -0.559741;
    CSPhiReweightParams.gamma_plus = 1.07196;
    CSPhiReweightParams.gamma_minus = 0.557244;
    PtYweights.at(2).at(5) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.574879;
    CSPhiReweightParams.alpha_minus = 0.13042;
    CSPhiReweightParams.beta_plus = 0.871515;
    CSPhiReweightParams.beta_minus = -0.211799;
    CSPhiReweightParams.gamma_plus = 0.368943;
    CSPhiReweightParams.gamma_minus = 0.104522;
    PtYweights.at(2).at(6) = CSPhiReweightParams;

    return PtYweights;

  }

  std::vector< std::vector<jFitParameters> > init_fit_params_CSPhi_Z_Old() {

    //to be used with the NT7 ZJets Madgraph sample - remember that we chose to look at the positively charge lepton explicitly
    jFitParameters CSPhiReweightParams;
    std::vector<std::vector<jFitParameters> > PtYweights(3, std::vector<jFitParameters>(7));
    CSPhiReweightParams.alpha_plus = 46.2809;
    CSPhiReweightParams.beta_plus = -0.121752;
    CSPhiReweightParams.gamma_plus = 1.6832;
    PtYweights.at(0).at(0) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 45.8962;
    CSPhiReweightParams.beta_plus = -0.682043;
    CSPhiReweightParams.gamma_plus = 0.60114;
    PtYweights.at(0).at(1) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 46.1772;
    CSPhiReweightParams.beta_plus = -0.658001;
    CSPhiReweightParams.gamma_plus = 1.28718;
    PtYweights.at(0).at(2) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 45.1491;
    CSPhiReweightParams.beta_plus = -0.562303;
    CSPhiReweightParams.gamma_plus = 0.979822;
    PtYweights.at(0).at(3) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 44.0444;
    CSPhiReweightParams.beta_plus = -0.277774;
    CSPhiReweightParams.gamma_plus = 0.117818;
    PtYweights.at(0).at(4) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 40.6353;
    CSPhiReweightParams.beta_plus = 0.102049;
    CSPhiReweightParams.gamma_plus = 0.381131;
    PtYweights.at(0).at(5) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 50.5398;
    CSPhiReweightParams.beta_plus = 0.13416;
    CSPhiReweightParams.gamma_plus = 2.44013;
    PtYweights.at(0).at(6) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.84752;
    CSPhiReweightParams.beta_plus = -0.107219;
    CSPhiReweightParams.gamma_plus = 1.28048;
    PtYweights.at(1).at(0) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.81071;
    CSPhiReweightParams.beta_plus = 0.00643131;
    CSPhiReweightParams.gamma_plus = 1.27896;
    PtYweights.at(1).at(1) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.73471;
    CSPhiReweightParams.beta_plus = 0.345532;
    CSPhiReweightParams.gamma_plus = 1.11864;
    PtYweights.at(1).at(2) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.57794;
    CSPhiReweightParams.beta_plus = -0.0824409;
    CSPhiReweightParams.gamma_plus = 1.36938;
    PtYweights.at(1).at(3) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 2.35352;
    CSPhiReweightParams.beta_plus = 0.075191;
    CSPhiReweightParams.gamma_plus = 1.0634;
    PtYweights.at(1).at(4) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 1.84518;
    CSPhiReweightParams.beta_plus = 0.22102;
    CSPhiReweightParams.gamma_plus = 0.888988;
    PtYweights.at(1).at(5) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 1.30486;
    CSPhiReweightParams.beta_plus = 0.167707;
    CSPhiReweightParams.gamma_plus = 0.633608;
    PtYweights.at(1).at(6) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.676971;
    CSPhiReweightParams.beta_plus = 0.0119424;
    CSPhiReweightParams.gamma_plus = 0.645641;
    PtYweights.at(2).at(0) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.635006;
    CSPhiReweightParams.beta_plus = 0.0761271;
    CSPhiReweightParams.gamma_plus = 0.507833;
    PtYweights.at(2).at(1) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.628758;
    CSPhiReweightParams.beta_plus = 0.0410792;
    CSPhiReweightParams.gamma_plus = 0.446003;
    PtYweights.at(2).at(2) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.563964;
    CSPhiReweightParams.beta_plus = 0.0701026;
    CSPhiReweightParams.gamma_plus = 0.500908;
    PtYweights.at(2).at(3) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.449677;
    CSPhiReweightParams.beta_plus = 0.0617526;
    CSPhiReweightParams.gamma_plus = 0.415034;
    PtYweights.at(2).at(4) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.268885;
    CSPhiReweightParams.beta_plus = 0.0845512;
    CSPhiReweightParams.gamma_plus = 0.24191;
    PtYweights.at(2).at(5) = CSPhiReweightParams;
    CSPhiReweightParams.alpha_plus = 0.0766288;
    CSPhiReweightParams.beta_plus = 0.018346;
    CSPhiReweightParams.gamma_plus = -0.00758775;
    PtYweights.at(2).at(6) = CSPhiReweightParams;

    return PtYweights;

  }


  std::vector< std::vector<jFitParameters> > init_fit_params_CSCosTheta_Z_Old() {
    //set blank for now - we moved to ICFv2 before I could code up the CosTheta Templates for the Z...
    jFitParameters CSCosThetaReweightParams;
    std::vector<std::vector<jFitParameters> > PtYweights(3, std::vector<jFitParameters>(7));
    CSCosThetaReweightParams.alpha_plus = 1.0;
    CSCosThetaReweightParams.beta_plus = 1.0;
    CSCosThetaReweightParams.gamma_plus = 1.0;
    PtYweights.at(0).at(0) = CSCosThetaReweightParams;
    PtYweights.at(0).at(1) = CSCosThetaReweightParams;
    PtYweights.at(0).at(2) = CSCosThetaReweightParams;
    PtYweights.at(0).at(3) = CSCosThetaReweightParams;
    PtYweights.at(0).at(4) = CSCosThetaReweightParams;
    PtYweights.at(0).at(5) = CSCosThetaReweightParams;
    PtYweights.at(0).at(6) = CSCosThetaReweightParams;
    PtYweights.at(1).at(0) = CSCosThetaReweightParams;
    PtYweights.at(1).at(1) = CSCosThetaReweightParams;
    PtYweights.at(1).at(2) = CSCosThetaReweightParams;
    PtYweights.at(1).at(3) = CSCosThetaReweightParams;
    PtYweights.at(1).at(4) = CSCosThetaReweightParams;
    PtYweights.at(1).at(5) = CSCosThetaReweightParams;
    PtYweights.at(1).at(6) = CSCosThetaReweightParams;
    PtYweights.at(2).at(0) = CSCosThetaReweightParams;
    PtYweights.at(2).at(1) = CSCosThetaReweightParams;
    PtYweights.at(2).at(2) = CSCosThetaReweightParams;
    PtYweights.at(2).at(3) = CSCosThetaReweightParams;
    PtYweights.at(2).at(4) = CSCosThetaReweightParams;
    PtYweights.at(2).at(5) = CSCosThetaReweightParams;
    PtYweights.at(2).at(6) = CSCosThetaReweightParams;

    return PtYweights;

    
  }



} //~namespace Operation

