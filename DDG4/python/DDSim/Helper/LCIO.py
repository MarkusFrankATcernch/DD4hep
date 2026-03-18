"""Helper object for files containing one or more MCParticle collections"""

from DDSim.Helper.Input import Input
from DDSim.Helper.MCParticle import MCParticleMixin


class LCIO(Input, MCParticleMixin):
  """Configuration for the LCIO input files"""

  def __init__(self):
    super(LCIO, self).__init__()
    self._parameters["MCParticleCollectionName"] = "MCParticle"
    self._closeProperties()
