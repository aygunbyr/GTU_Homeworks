from django.db import models
from django.urls import reverse
from django.utils.text import slugify
from ckeditor.fields import RichTextField

# Create your models here.

class Post(models.Model):
    user = models.ForeignKey('auth.User', on_delete=models.CASCADE, verbose_name='Author', related_name='posts')
    title = models.CharField(max_length=120, verbose_name='Title')
    content = RichTextField(verbose_name='Content')
    publishing_date = models.DateTimeField(verbose_name='Release Date', auto_now_add=True)
    image = models.ImageField(null=True, blank=True, verbose_name='Cover Photo')
    slug = models.SlugField(unique=True, editable=False, max_length=130, verbose_name='Dynamic Linkage')
    category = models.ForeignKey('post.Category', on_delete=models.CASCADE, related_name='posts', verbose_name='Post Category')
    view_count = models.IntegerField(verbose_name='Number of views', default=0)


    def __str__(self):
        return self.title

    def get_absolute_url(self):
        return reverse('post:detail', kwargs={'slug': self.slug})
        # return "/post/{}".format(self.id)

    def get_create_url(self):
        return reverse('post:create')
        # return "/post/{}".format(self.id)

    def get_update_url(self):
        return reverse('post:update', kwargs={'slug': self.slug})
        # return "/post/{}".format(self.id)

    def get_delete_url(self):
        return reverse('post:delete', kwargs={'slug': self.slug})
        # return "/post/{}".format(self.id)

    def get_unique_slug(self):
        slug = slugify(self.title.replace('ı', 'i'))
        unique_slug = slug
        counter = 1
        while Post.objects.filter(slug=unique_slug).exists():
            unique_slug = '{}-{}'.format(slug, counter)
            counter += 1
        return unique_slug

    def save(self, *args, **kwargs):
        self.slug = self.get_unique_slug()
        return super(Post, self).save(*args, **kwargs)


    class Meta:
        ordering = ['-publishing_date', 'id']

class Comment(models.Model):
    post = models.ForeignKey('post.Post', related_name='comments', on_delete=models.CASCADE, verbose_name='Post')
    author = models.ForeignKey('auth.User', related_name='comments', on_delete=models.CASCADE, verbose_name='Author')
    name = models.CharField(max_length=200, verbose_name='Title')
    content = models.TextField(verbose_name='Comment')
    created_date = models.DateTimeField(auto_now_add=True, verbose_name='Created Date')
    is_approved = models.BooleanField(default=False, verbose_name='Approval status')


    def __str__(self):
        return self.content

class Category(models.Model):
    name = models.CharField(max_length=255)
    image = models.ImageField(null=True, blank=True)
    slug = models.SlugField(unique=True, editable=False, max_length=130)

    def get_unique_slug(self):
        slug = slugify(self.name.replace('ı', 'i'))
        unique_slug = slug
        counter = 1
        while Category.objects.filter(slug=unique_slug).exists():
            unique_slug = '{}-{}'.format(slug, counter)
            counter += 1
        return unique_slug

    def save(self, *args, **kwargs):
        self.slug = self.get_unique_slug()
        return super(Category, self).save(*args, **kwargs)



    def __str__(self):
        return self.name

