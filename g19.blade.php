@@section('content')

@if(Auth::user()->name == "g19")


 	<script src="{{ asset('js/three.js') }}"></script>
 	<script src="{{ asset('js/OrbitControls.js') }}"></script>
 	<script src="{{ asset('js/OBJLoader.js') }}"></script>
 	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>

	<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
        <style>
        body {
            margin: 0;
        }

        canvas {
            width: 100%;
            height: 100%;
        }
        #control_panel{
        	border:solid 3px white;
        	position: absolute;
        	top: 10;
        	left: 10;
        	color:white;
        	width: 20%;
        	text-align: center;
        }
		hr.myhr {
			border-top: 1px solid white;
	      	margin-left : 10%;
        	margin-right : 10%;
		}

    </style>
    <body>
    	<div id="control_panel">
    		<h1 style="padding-top:1%;color:white">Control Panel</h1>
    		<hr class="myhr">
    		<h3> Load  Models </h3>
    		<div class="dropdown">
	            <select id="objSelect"> 
	                <option value="-1"></option> 
	                @foreach($obj_array as $obj)
	                	@if($obj == "." || $obj == "..")
	                		@continue
	                	@endif
	                    <option value="{{$obj}}" onclick="loadModel('{{$obj}}')">{{$obj}}</option> 
	                @endforeach
	            </select> 
        	</div>
        	<p id="details_obj"><p>


    		<hr class="myhr">
    		<h3> Options </h3>
			<div class="form-check">
			    <input type="checkbox" class="form-check-input" id="wave_checkbox">
			    <label class="form-check-label" for="wave_checkbox">Wave movement</label>
			</div>
			<div class="form-check">
			    <input type="checkbox" class="form-check-input" id="hor_checkbox">
			    <label class="form-check-label" for="hor_checkbox">Horizontal Rotation</label>
   			</div>
			<div class="form-check">
			    <input type="checkbox" class="form-check-input" id="ver_checkbox">
			    <label class="form-check-label" for="ver_checkbox">Vertical Rotation</label>
   			</div>

			<br><br>
			<div>
				<button type="button" class="btn btn-danger" onclick="cleanScene()">
					Clean Scene 
				</button>
				<button type="button" class="btn btn-warning" onclick="resetPosition()">
					Reset Postition 
				</button>
				<br>
				<br>
			</div>
    	</div>
		<div style="position: absolute;bottom: 0;right: 0%">
    		<h3 style="color:white;"> Theodoros Mandilaras cs21900018</h3>
    	</div>


	    <script>
	        var scene = new THREE.Scene();
	        var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000)

	        var renderer = new THREE.WebGLRenderer();
	        renderer.setSize(window.innerWidth, window.innerHeight);

	        document.body.appendChild(renderer.domElement);

	        window.addEventListener( 'resize', function(){
	            var width = window.innerWidth;
	            var height = window.innerHeight;
	            renderer.setSize( width, height);
	            camera.aspect = width/height;
	            camera.updateProjectionMatrix();
	        });

	        controls = new THREE.OrbitControls( camera, renderer.domElement);
	        var current_objet;
	        var current_objet_file;
	        var loader = new THREE.OBJLoader( );


	        function loadModel(model_path){
	        	current_objet_file = "{{asset('storage/g/')}}/"+model_path;
		        loader.load(
		        	// resource URL
		            "{{asset('storage/g/')}}/"+model_path,
		            function(object){
		            	cleanScene();
		                console.log("loadded!");

		                object.traverse( function( child ) {
			            if (child instanceof THREE.Mesh ) {
			                child.material = new THREE.MeshBasicMaterial({ color:0xFFFFFF, wireframe: true});
			            }
			        	});
		                scene.add(object);
		                current_objet = object;

		                //get details ---
		                $.ajax({
					        type: "POST",
					        async: true,
					        headers: {
					            'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')
					        },
					        url: "http://ec2-15-188-40-183.eu-west-3.compute.amazonaws.com/getdetails",
					        dataType:'JSON',
					        data: {
					            _token : $('meta[name="csrf-token"]').attr('content'),
					            "obj_name" : model_path,
					        }, 
					        success: function(response){
					            console.log(JSON.stringify(response));
					            details = JSON.parse(JSON.stringify(response));
					            document.getElementById('details_obj').innerHTML = "Faces: " + details.f + " Vertices: " + details.v;
					        },
					        timeout: 5000
					    })
					    .fail(function() {
					        alert('Error! Json Post Failed!');
					    });
					    //----
		            },
		            // called when loading is in progresses
					function ( xhr ) {
						console.log( ( xhr.loaded / xhr.total * 100 ) + '% loaded' );
					},
					// called when loading has errors
					function ( error ) {
						console.log( 'An error happened' );
					}
		        );
		    }

		    function cleanScene(){
		    	if(current_objet != null)
		    		scene.remove(current_objet);
		    }
		    function resetPosition(){
		    	console.log(current_objet);
		    	current_objet.rotation.x = 0;
		    	current_objet.rotation.y = 0;
		    	current_objet.rotation.z = 0;


		    }


	        camera.position.z = 40;

	        var ambient_light = new THREE.AmbientLight(0xffffff, 3.0);
	        scene.add( ambient_light );

	        // game logic
	        var update = function () {
	        	if(document.getElementById("wave_checkbox").checked){
		            current_objet.rotation.x += 0.01;
		            current_objet.rotation.y += 0.005;
		        }
		        if(document.getElementById("hor_checkbox").checked){
		            current_objet.rotation.y += 0.005;
		        }
		        if(document.getElementById("ver_checkbox").checked){
		            current_objet.rotation.x += 0.005;
		        }
	        };

	        //draw Scene
	        var render = function () {
	            renderer.render(scene, camera);

	        };

	        // rn game loop (update, render, repeat)
	        var GameLoop = function () {
	            requestAnimationFrame(GameLoop);

	            update();
	            render();
	        };


	        GameLoop(); 
	    </script>
    </body>

@else
	<div class="container">
		<center>
			<h1 style="color:gold;margin-top: 20%">None</h1>
		</center>
	</div>
@endif




// ------------------------ backend code:

    public function g19(){
        $obj_array = scandir("storage/g/");
        return view("g19")->with('obj_array', $obj_array);
    }

    public function countVF(Request $request){
        $vertices = 0;
        $faces = 0;

        $fn = fopen("storage/g/".$request->input("obj_name"),"r");
        while(! feof($fn))  {
            $line = fgets($fn);
            if (strpos($line, 'v') !== false) {
                $vertices +=1;
            }
            if (strpos($line, 'f') !== false) {
                $faces +=1;
            }
            
        }

        fclose($fn);
        return json_encode(["f"=>$faces, "v"=>$vertices]);
    }


}
