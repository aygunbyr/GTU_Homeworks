from django.contrib import admin
from .models import Post, Comment, Category

class PostAdmin(admin.ModelAdmin):

    list_display = ['title', 'user', 'category', 'publishing_date', 'slug']
    list_display_links = ['title', 'publishing_date']
    list_filter = ['publishing_date', 'category']
    search_fields = ['title', 'content']

    class Meta:
        model = Post

admin.site.register(Post, PostAdmin)

class CommentAdmin(admin.ModelAdmin):
    class Meta:
        model = Comment

    list_display = ['name', 'author', 'post', 'content', 'created_date', 'is_approved']
    list_filter = ['is_approved', 'created_date']


admin.site.register(Comment, CommentAdmin)

class CategoryAdmin(admin.ModelAdmin):
    class Meta:
        model = Category

    list_display = ['name', 'slug']

admin.site.register(Category, CategoryAdmin)
