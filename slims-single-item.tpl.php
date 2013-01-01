<div class="<?php print $classes; ?>">
  <div class="image"><?php print $image;?></div>
  <h3 class="title"><?php print render($title); ?></h3>
  <?php if(isset($authors) AND trim($authors) != ''):?><div class="name"><?php print $authors; ?></div><?php endif;?>
</div>
