let sidebar = document.querySelector(".sidebar");
let sidebarBtn = document.querySelector(".sidebarBtn");
sidebarBtn.onclick = function () {
  sidebar.classList.toggle("active");
  if (sidebar.classList.contains("active")) {
    sidebarBtn.classList.replace("bx-menu", "bx-menu-alt-right");
  } else
    sidebarBtn.classList.replace("bx-menu-alt-right", "bx-menu");
}



// $(document).ready(function () {
//   $('#plantType').change(function () {
//     var plantType = $(this).val();
//     $.ajax({
//       url: "fetch_plant_type.php",
//       method: "POST",
//       data: { plantType: plantType },
//       success: function (data) {
//         $('#showPlantDetails').html(data);
//       }
//     });
//   });
// });

