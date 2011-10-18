import setupSUSY
from libFrameworkSUSY import *
from libOneLepton import *
from copy import deepcopy

#from SingleMu_Run2011A_skim import *

from data.Mu_Run2010A_Nov4ReReco_v1 import *
from data.Mu_Run2010B_Nov4ReReco_v1 import *
from data.Run2011.SingleMu_uptoRun163817 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v1 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v2_a import *
from data.Run2011.MuHad_Run2011A_PromptReco_v2_b import *
from data.Run2011.MuHad_Run2011A_PromptReco_v2_c import *
from data.Run2011.SingleMu_Run2011A_May10ReReco_v1_Preliminary import *

## ntuples using the latest MuID recipe

from data.Run2011.SingleMu_Run2011A_May10ReReco_v1_NewMuRecipe import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_NewMuRecipe_a import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_NewMuRecipe_b import *

from data.Run2011.SingleMu_Run2011A_May10ReReco_v1_V15_03_05 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_d_V15_03_05 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_c_V15_03_05 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_b_V15_03_05 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_a_V15_03_05 import *

## 2011 Data :: CMSSSW_42X PromptReco && May10ReReco

## Muons
from data.Run2011.SingleMu_Run2011A_May10ReReco_v1 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_b import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_c import *

from data.Run2011.MuHad_Run2011A_May10ReReco_v1 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v4 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v4_b import *
from data.Run2011.MuHad_Run2011A_PromptReco_v4_c import *

from data.Run2011.MuHad_Run2011A_May10ReReco_v1_V15_03_05 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v4_V15_03_05 import *

from data.Run2011.MuHad_Run2011A_May10ReReco_v1_V15_03_14 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v4_V15_03_14  import *

from data.Run2011.SingleMu_Run2011A_May10ReReco_v1_V15_03_14 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_V15_03_14  import *

from data.Run2011.SingleMu_Run2011A_PromptReco_v4_V15_03_14_residual  import *
from data.Run2011.SingleMu_Run2011A_May10ReReco_v1_V15_03_14_residual import *


from data.Run2011.MuHad_Run2011A_PromptReco_v4_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1  import *
from data.Run2011.MuHad_Run2011A_May10ReReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *

## Electrons
from data.Run2011.ElectronHad_Run2011A_May10ReReco_v1_RA4 import *
from data.Run2011.ElectronHad_Run2011A_PromptReco_v4_RA4 import *

from data.Run2011.SingleElectron_Run2011A_May10ReReco_v1 import *


from data.Run2011.ElectronHad_Run2011A_May10ReReco_v1_V15_03_14 import *
from data.Run2011.ElectronHad_Run2011A_PromptReco_v4_V15_03_14  import *

from data.Run2011.ElectronHad_Run2011A_May10ReReco_v1_V15_03_14_residual import *
from data.Run2011.ElectronHad_Run2011A_PromptReco_v4_V15_03_14_residual  import *

from data.Run2011.ElectronHad_Run2011A_05Aug2011_v1_V15_03_14_residual    import *
from data.Run2011.ElectronHad_Run2011A_PromptReco_v6_V15_03_14_residual   import *
from data.Run2011.ElectronHad_Run2011B_PromptReco_v1_V15_03_14_residual_a import *
from data.Run2011.ElectronHad_Run2011B_PromptReco_v1_V15_03_14_residual_b import *
from data.Run2011.ElectronHad_Run2011B_PromptReco_v1_V15_03_14_residual_c import *



from data.Run2011.MuHad_Run2011A_05Aug2011_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.MuHad_Run2011B_PromptReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1_a import *
from data.Run2011.MuHad_Run2011B_PromptReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1_b import *
from data.Run2011.MuHad_Run2011B_PromptReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1_c import *
from data.Run2011.MuHad_Run2011A_PromptReco_v6_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v6_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_Sync import *

#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_a import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_b import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_c import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_d import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_e import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_f import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v4_g import *

## import the 2011 data PSets in CMSSW_41X
#from data.Run2011.HT_Run2011A_PromptReco_v1 import *

#from data.Run2011.HT_Run2011_promptReco import *
#from data.Run2011.SingleMu_Run2011A_PromptReco_v1 import *
#from data.Run2011.SingleMu_Run2011A_PromptReco_v2 import *
#from data.Run2011.SingleElectron_Run2011A_PromptReco_v1 import *

sample_Fall11 = [
#    MuHad_Run2011A_PromptReco_v6_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_Sync
MuHad_Run2011A_05Aug2011_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1,
MuHad_Run2011B_PromptReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1_a,
MuHad_Run2011B_PromptReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1_b,
MuHad_Run2011B_PromptReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1_c,
MuHad_Run2011A_PromptReco_v6_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1
    ]

samplesDataSiMuNew = [
    SingleMu_Run2011A_May10ReReco_v1_V15_03_14_residual,
   # SingleMu_Run2011A_May10ReReco_v1_V15_03_14
]
samplesDataSiMuNewPromt = [
SingleMu_Run2011A_PromptReco_v4_V15_03_14_residual,
    ]

samplesDataMuHadresidualMay = [

MuHad_Run2011A_May10ReReco_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1,

    ]
samplesDataMuHadresidualPrompt = [
MuHad_Run2011A_PromptReco_v4_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1
    ]


samplesData = [Mu_Run2010A_Nov4ReReco_v1,Mu_Run2010B_Nov4ReReco_v1]    
#samplesData = [SingleMu_Run2011A_PromptReco_v1, SingleMu_Run2011A_PromptReco_v2]

samplesData311 = [
    SingleMu_uptoRun163817,
    MuHad_Run2011A_PromptReco_v1,
    MuHad_Run2011A_PromptReco_v2_a,
    MuHad_Run2011A_PromptReco_v2_b,
    MuHad_Run2011A_PromptReco_v2_c
    ]


samplesData42X = [
    SingleMu_Run2011A_May10ReReco_v1_Preliminary
    ]


## CMSSW_42X samples


samplesData42X_MuHad_ReReco = [
    MuHad_Run2011A_May10ReReco_v1_V15_03_05
    #MuHad_Run2011A_May10ReReco_v1
    ]

samplesData42X_MuHad_PromptReco = [
  #  MuHad_Run2011A_PromptReco_v4,
   # MuHad_Run2011A_PromptReco_v4_b,
   # MuHad_Run2011A_PromptReco_v4_c
    MuHad_Run2011A_PromptReco_v4_V15_03_05
    ]

samplesData42X_SingleMu_ReReco = [
 #   SingleMu_Run2011A_May10ReReco_v1
    SingleMu_Run2011A_May10ReReco_v1_V15_03_05
    ]

samplesData42X_SingleMu_PromptReco = [
 #   SingleMu_Run2011A_PromptReco_v4,
 #   SingleMu_Run2011A_PromptReco_v4_b,
 #   SingleMu_Run2011A_PromptReco_v4_c
SingleMu_Run2011A_PromptReco_v4_d_V15_03_05,
SingleMu_Run2011A_PromptReco_v4_c_V15_03_05,
SingleMu_Run2011A_PromptReco_v4_b_V15_03_05,
SingleMu_Run2011A_PromptReco_v4_a_V15_03_05
    ]

## access samples using the latest Ntuples

samplesData42X_SingleMu_ReReco_NewMuRecipe = [
    SingleMu_Run2011A_May10ReReco_v1_NewMuRecipe
    ]

samplesData42X_SingleMu_PromptReco_NewMuRecipe = [
    SingleMu_Run2011A_PromptReco_v4_NewMuRecipe_a,
    SingleMu_Run2011A_PromptReco_v4_NewMuRecipe_b
    ]


#SingleMu_skim = [SingleMu_Run2011A_skim]

samplesData42X_MuHad = [
    MuHad_Run2011A_May10ReReco_v1,
    MuHad_Run2011A_PromptReco_v4
    ]

samplesData42X_ElHad_PromptReco = [
#    ElectronHad_Run2011A_May10ReReco_v1,
    ElectronHad_Run2011A_PromptReco_v4
    ]

samplesData42X_ElHad_ReReco = [
    ElectronHad_Run2011A_May10ReReco_v1
    #ElectronHad_Run2011A_PromptReco_v4
            ]

samplesData42X_SingleMu = [
    SingleMu_Run2011A_May10ReReco_v1,
    SingleMu_Run2011A_PromptReco_v4,
    SingleMu_Run2011A_PromptReco_v4_b
    ]

samplesData42X_SingleEl_ReReco = [
    SingleElectron_Run2011A_May10ReReco_v1
#    SingleElectron_Run2011A_PromptReco_v4 ## not yet ready
    ]



### V15_03_14 DATA samples


samplesData42X_MuHad_RR_V15_03_14 = [
    MuHad_Run2011A_May10ReReco_v1_V15_03_14
    ]

samplesData42X_MuHad_PR_V15_03_14 = [
    MuHad_Run2011A_PromptReco_v4_V15_03_14
    ]


samplesData42X_SingleMu_RR_V15_03_14 = [
    SingleMu_Run2011A_May10ReReco_v1_V15_03_14
    ]

samplesData42X_SingleMu_PR_V15_03_14 = [
    SingleMu_Run2011A_PromptReco_v4_V15_03_14
    ]


samplesData42X_ElHad_RR_V15_03_14 = [
    ElectronHad_Run2011A_May10ReReco_v1_V15_03_14
    ]

samplesData42X_ElHad_PR_V15_03_14 = [
    ElectronHad_Run2011A_PromptReco_v4_V15_03_14
    ]


samplesData42X_SingleMu_RR_V15_03_14_residual = [
    SingleMu_Run2011A_PromptReco_v4_V15_03_14_residual
    ]

samplesData42X_SingleMu_PR_V15_03_14_residual = [
    SingleMu_Run2011A_PromptReco_v4_V15_03_14_residual
    ]

samplesData42X_ElHad_RR_V15_03_14_residual = [
    ElectronHad_Run2011A_May10ReReco_v1_V15_03_14_residual
    ]

samplesData42X_ElHad_PR_V15_03_14_residual = [
    ElectronHad_Run2011A_PromptReco_v4_V15_03_14_residual,
    ElectronHad_Run2011A_05Aug2011_v1_V15_03_14_residual,
    ElectronHad_Run2011A_PromptReco_v6_V15_03_14_residual,
    ElectronHad_Run2011B_PromptReco_v1_V15_03_14_residual_a,
    ElectronHad_Run2011B_PromptReco_v1_V15_03_14_residual_b,
    ElectronHad_Run2011B_PromptReco_v1_V15_03_14_residual_c
    ]



#samplesData42X_SingleEl_PromptReco = [
#    SingleElectron_Run2011A_PromptReco_v4_a,
#    SingleElectron_Run2011A_PromptReco_v4_b,
#    SingleElectron_Run2011A_PromptReco_v4_c,
#    SingleElectron_Run2011A_PromptReco_v4_d,
#    SingleElectron_Run2011A_PromptReco_v4_e,
#    SingleElectron_Run2011A_PromptReco_v4_f,
#    SingleElectron_Run2011A_PromptReco_v4_g
#    ]

