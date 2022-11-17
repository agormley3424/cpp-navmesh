
-- this script is in lua format
-- this is a meta script that fills in data that is passed to 'myScript' that in turn calls C++ function
-- some of the data can be set by default, some of the data might be required to be edited from maya
function fillMetaInfoTable(args) -- the script fromat requires existance of this function

-- user modifed data
args['myScript']="navCell.lua"
args['myScriptPackage']="CharacterControl"

args['id'] = ''
args['neighbor1'] = '-1'
args['neighbor2'] = '-1'
args['neighbor3'] = '-1'
args['neighbor4'] = '-1'
args['value'] = '0'
args['shape'] = 'rectangle'


end -- required
