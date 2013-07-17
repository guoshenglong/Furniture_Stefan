var showGeometries = false;
var manVisible = false;
var chairVisible = false;
var tvVisible = false;


arel.sceneReady(function()

{

       arel.Scene.setTrackingConfiguration("ORIENTATION_FLOOR");

       //get the metaio man model reference
       var metaioMan = arel.Object.Model3D.create("1","Assets7/metaioman.md2","Assets7/metaioman.png");
       metaioMan.setVisibility(false);
       metaioMan.setCoordinateSystemID(1);
       metaioMan.setScale(new arel.Vector3D(10.0,10.0,10.0));
       arel.Scene.addObject(metaioMan);
       metaioMan.setPickingEnabled(true);
       // handle animation for metaioMan
       arel.Events.setListener(metaioMan, function(obj, type, params){handleMetaioManEvents(obj, type, params);});


       // get chair model reference
       var chair = arel.Object.Model3D.create("2","Assets7/stuhl.obj","Assets7/stuhl.jpg");
       chair.setVisibility(false);
       chair.setCoordinateSystemID(1);
       chair.setScale(new arel.Vector3D(100.0,100.0,100.0));
       var chairRotation = new arel.Rotation();
       chairRotation.setFromEulerAngleDegrees(new arel.Vector3D(90.0,0.0,0.0));
       chair.setRotation(chairRotation);
       arel.Scene.addObject(chair);        
       chair.setPickingEnabled(true);


       var tv = arel.Object.Model3D.create("3","Assets7/tv.obj","Assets7/tv.png");
       tv.setVisibility(false);
       tv.setCoordinateSystemID(1);
       tv.setScale(new arel.Vector3D(100.0,100.0,100.0));
       var tvRotation = new arel.Rotation();
       tvRotation.setFromEulerAngleDegrees(new arel.Vector3D(90.0,0.0,0.0));
       tv.setRotation(tvRotation);
       arel.Scene.addObject(tv);
       tv.setPickingEnabled(true);
  
                
       // the parameters for the screen should be in agreement with those of the TV
       var screen = arel.Object.Model3D.create("4","Assets7/screen.obj");
       screen.setVisibility(false);
       screen.setCoordinateSystemID(1);
       screen.setScale(new arel.Vector3D(100.0,100.0,100.0));
       screen.setRotation(tvRotation);	   
	   screen.setMovie("Assets7/sintel.3g2");
       arel.Scene.addObject(screen);
       screen.setPickingEnabled(true);
                


});




function handleMetaioManEvents(obj, type, param)
{
	console.log("fubar");
    
	//check if there is tracking information available
	if(type && type === arel.Events.Object.ONTOUCHSTARTED)
	{
		obj.startAnimation("shock_down");
	}
	else if(type && type === arel.Events.Object.ONANIMATIONENDED && param.animationname == "shock_down")
	{
		obj.startAnimation("close_idle");
	}
    else if(type && type === arel.Events.Object.ONANIMATIONENDED && param.animationname == "close_idle")
	{
		obj.startAnimation("close_up");
	}
};



function clickHandler()

{

    var idClicked = $("#radio :radio:checked").attr('id');

    if (idClicked == 'radio1')

    {
        arel.Scene.setFreezeTracking(true);
        
        // get the 3d position of the center of the screen to set the translation of geometries
        arel.Scene.get3DPositionFromScreenCoordinates(new arel.Vector2D(0.5,0.5),1,function(trans){translation(trans);});

    }

    if (idClicked == 'radio2')

    {

        showGeometries = false;
        
        // hide the geometries before reactivate the camera
        arel.Scene.getObject("1").setVisibility(false);
        arel.Scene.getObject("2").setVisibility(false);
        arel.Scene.getObject("3").setVisibility(false);
        arel.Scene.getObject("4").setVisibility(false);
		arel.Scene.getObject("4").stopMovieTexture();
        
        // remove the geometries to the gesture handler
        arel.GestureHandler.removeObject( "1" );
        arel.GestureHandler.removeObject( "2" );
        arel.GestureHandler.removeObject( "3" );
        arel.GestureHandler.removeObject( "4" );

        
		manVisible = false;
        chairVisible = false
        tvVisible = false;
        
        // change the button image to unselected
		document.getElementById("manImage").src = "Assets7/button_man_unselected.png";		
		document.getElementById("chairImage").src = "Assets7/button_chair_unselected.png";		
		document.getElementById("tvImage").src = "Assets7/button_tv_unselected.png";

        arel.Scene.setFreezeTracking(false);
        arel.Scene.setTrackingConfiguration("ORIENTATION_FLOOR");

    }

};


function translation(trans)

{
    
    // add the geometries to the gesture handler
    arel.GestureHandler.addObject( "1", 1 );
    arel.GestureHandler.addObject( "2", 2 );
    arel.GestureHandler.addObject( "3", 3 );
    arel.GestureHandler.addObject( "4", 3 );

    // set the translation of the geometires according to the current coordinate system
    var metaioMan = arel.Scene.getObject("1");
    metaioMan.setTranslation(trans);
    metaioMan.setVisibility(true);
    document.getElementById("manImage").src = "Assets7/button_man_selected.png";
    manVisible = true;
    
    
    var chair = arel.Scene.getObject("2");
    chair.setTranslation(trans);
    chair.setVisibility(true);
    document.getElementById("chairImage").src = "Assets7/button_chair_selected.png";
    chairVisible = true;
    
    var tv = arel.Scene.getObject("3");
    tv.setTranslation(trans);
    tv.setVisibility(true);
    document.getElementById("tvImage").src = "Assets7/button_tv_selected.png";
    tvVisible = true;
    
    var screen = arel.Scene.getObject("4");
    screen.setTranslation(trans);
    screen.setVisibility(true);
    screen.startMovieTexture();
    
    showGeometries = true;
	

};



function onManPushed()

{

    // image button not pushable if the camera is still active
    if (showGeometries)

    {
        // if metaioMan not visible, set it to visible and reset the parameters
        if (!manVisible)

        {
            arel.Scene.getObject("1").setScale(new arel.Vector3D(10.0,10.0,10.0));
            arel.Scene.get3DPositionFromScreenCoordinates(new arel.Vector2D(0.5,0.5),1,function(trans){translationMan(trans);});
            document.getElementById("manImage").src = "Assets7/button_man_selected.png";            
			manVisible = true;

        }

        else

        {
            arel.Scene.getObject("1").setVisibility(false);
            document.getElementById("manImage").src = "Assets7/button_man_unselected.png";			
			manVisible = false;

        }
    }
    else
    {
        alert("Please take a picture first!");
    }

};


function translationMan(trans)

{

    arel.Scene.getObject("1").setTranslation(trans);
    arel.Scene.getObject("1").setVisibility(true);	
    

};


function onChairPushed()

{

    if (showGeometries)

    {	    
        if (!chairVisible)

        {
            arel.Scene.getObject("2").setScale(new arel.Vector3D(100.0,100.0,100.0));
            arel.Scene.get3DPositionFromScreenCoordinates(new arel.Vector2D(0.5,0.5),1,function(trans){translationChair(trans);});
            document.getElementById("chairImage").src = "Assets7/button_chair_selected.png";			
			chairVisible = true;

        }

        else

        {

            arel.Scene.getObject("2").setVisibility(false);
            document.getElementById("chairImage").src = "Assets7/button_chair_unselected.png";			
			chairVisible = false;

        }


    }
    else
    {
        alert("Please take a picture first!");
    }

};


function translationChair(trans)

{
    arel.Scene.getObject("2").setTranslation(trans);
    arel.Scene.getObject("2").setVisibility(true);

};


function onTVPushed()

{

    if (showGeometries)

    {
        if (!tvVisible)

        {
            arel.Scene.getObject("3").setScale(new arel.Vector3D(100.0,100.0,100.0));			
			arel.Scene.getObject("4").setScale(new arel.Vector3D(100.0,100.0,100.0));
            arel.Scene.get3DPositionFromScreenCoordinates(new arel.Vector2D(0.5,0.5),1,function(trans){translationTV(trans);});
            document.getElementById("tvImage").src = "Assets7/button_tv_selected.png";			
			tvVisible = true;

        }

        else

        {
            arel.Scene.getObject("3").setVisibility(false);			
			arel.Scene.getObject("4").setVisibility(false);			
			arel.Scene.getObject("4").stopMovieTexture();
            document.getElementById("tvImage").src = "Assets7/button_tv_unselected.png";			
			tvVisible = false;

        }

    }
    else
    {
        alert("Please take a picture first!");
    }

};


function translationTV(trans)

{
    arel.Scene.getObject("3").setTranslation(trans);
    arel.Scene.getObject("4").setTranslation(trans);
    arel.Scene.getObject("3").setVisibility(true);
    arel.Scene.getObject("4").setVisibility(true);	
	arel.Scene.getObject("4").startMovieTexture();

};