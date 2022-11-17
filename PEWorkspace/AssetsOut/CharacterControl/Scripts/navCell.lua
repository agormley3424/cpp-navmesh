

-- expected arguments:

outputDebugString("Executing navCell.lua (note: this will probably just define functions like runScript(args)\n")

function runScript(args)
	outputDebugString("PE: Progress: navCell.lua runScript() Entry...\n")

    -- Where is the base information coming from? Is there an interface between the python file and this that adds these that I should know about?
    local pos = args['base']['pos']
    local u = args['base']['u']
    local v = args['base']['v']
    local n = args['base']['n']
    
    outputDebugString("PE: Progress: about to call root.CharacterControl.Events.Event_CREATE_NAVCELL.Construct\n")

    evt = root.CharacterControl.Events.Event_CREATE_NAVCELL.Construct(
        args['shape'],
        args['id'],
        args['neighbor1'],
        args['neighbor2'],
        args['neighbor3'],
        args['neighbor4'],
        args['value'],
        pos[1], pos[2], pos[3],
        u[1], u[2], u[3],
        v[1], v[2], v[3],
        n[1], n[2], n[3],
        args['peuuid'] --What is this, what is it for?
    )
    outputDebugString("PE: Progress: about to call getGameObjectManagerHandle()\n")

    handler = getGameObjectManagerHandle(l_getGameContext())
    outputDebugString("PE: Progress: about to call root.PE.Components.Component.SendEventToHandle(handler, evt)\n")

	root.PE.Components.Component.SendEventToHandle(handler, evt)
end
